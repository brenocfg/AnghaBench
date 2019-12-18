#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct memcache_server_functions {TYPE_2__* info; } ;
struct gather_data {int ready_num; int wait_num; double start_time; } ;
struct connection {int /*<<< orphan*/  In; } ;
struct conn_query {scalar_t__ req_generation; int extra; TYPE_1__* requester; } ;
struct TYPE_4__ {int /*<<< orphan*/  mc_proxy_inbound; } ;
struct TYPE_3__ {scalar_t__ generation; int /*<<< orphan*/ * extra; } ;

/* Variables and functions */
 TYPE_2__* CC ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int DATA_BUFF_LEN ; 
 struct gather_data* GATHER_QUERY (struct conn_query*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  client_read_special (struct conn_query*,int*,int) ; 
 char* cur_key ; 
 int* data_buff ; 
 int /*<<< orphan*/  delete_search_query (struct conn_query*) ; 
 int /*<<< orphan*/  end_search_query (struct conn_query*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_unused_buffers (int /*<<< orphan*/ *) ; 
 struct conn_query* get_conn_query (struct connection*,int*,int) ; 
 double get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_complete_custom (struct conn_query*,int) ; 
 int read_in (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int search_merge (struct connection *c, int data_len) {
  assert (data_len <= DATA_BUFF_LEN);
  
  assert (read_in (&c->In, data_buff, data_len) == data_len);
  if (verbosity >= 4) {
    int i;
    for (i = 0; i < data_len; i++) 
      fprintf (stderr, "%c[%d]", data_buff[i], data_buff[i]);
    fprintf (stderr, "\n");
  }
  free_unused_buffers (&c->In);

  int data_shift = 0;
  while (data_shift < data_len && data_buff[data_shift] != 13) {
    data_shift++;
  }
  if (data_shift >= data_len-1) {
    fprintf (stderr, "data_shift = %d\n", data_shift);
    return -1;
  }
  data_shift += 2;
  if (data_buff[data_shift-1] != 10) {
    fprintf (stderr, "data_buff[] = %d\n", data_buff[data_shift-1]);
    return -1;
  }

  struct conn_query *q = get_conn_query (c, data_buff, data_len);

  if (!q) {
    fprintf (stderr, "Error in search_merge: cannot find query for answer. Dropping answer.\n");
    return 0;
  }

  if (!q->requester || q->req_generation != q->requester->generation) {
    fprintf (stderr, "Error in search_merge: generations do not match. Dropping answer. (key = %s).\n", cur_key);
    query_complete_custom (q, 0);
    return 0;
  }

  struct conn_query *Q = (struct conn_query*)q->extra; 
  if (!Q) {
    fprintf (stderr, "Error in search_merge: no parent query. Dropping answer. (key = %s).\n", cur_key);
    query_complete_custom (q, 0);
    return 0;
  }
  assert (q->requester == Q->requester);
  assert (Q->extra);


  CC = ((struct memcache_server_functions *) (Q->requester)->extra)->info;
  assert (CC && &CC->mc_proxy_inbound == (Q->requester)->extra);
  
  client_read_special (q, data_buff + data_shift, data_len - data_shift);
  query_complete_custom (q, 1);

  if (verbosity >= 4) {
    fprintf (stderr, "end of search_merge\n");
  }

  struct gather_data *G = GATHER_QUERY(Q);
  if (verbosity >= 2) {
  	fprintf (stderr, "got answer %d of %d in %.08f seconds\n", G->ready_num, G->wait_num, get_utime(CLOCK_MONOTONIC) - G->start_time);
  }

  if (G->wait_num == G->ready_num) {
    end_search_query (Q);
    if (verbosity >= 4) {
      fprintf (stderr, "All answers gathered. Deleting master query.\n");
    }
    //query_complete (Q->requester, 1);
    delete_search_query (Q);
  }

  return 1;
}