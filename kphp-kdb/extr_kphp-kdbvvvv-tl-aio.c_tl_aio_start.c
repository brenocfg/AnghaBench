#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tl_saved_query {int wait_num; int /*<<< orphan*/  attempt; struct aio_connection** restart; } ;
struct aio_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * Connections ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  default_tl_aio_metafile_query_type ; 
 int /*<<< orphan*/  tl_create_aio_query (struct aio_connection*,int /*<<< orphan*/ *,double,int /*<<< orphan*/ *,struct tl_saved_query*) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int tl_aio_start (struct aio_connection **aio_connections, int conn_num, double timeout, struct tl_saved_query *q) {
  assert (q->restart);
  q->attempt ++;

  assert (conn_num >= 0);
  if (!conn_num) {
    return 0;
  }

  int i;
  for (i = 0; i < conn_num; i++) {
    assert (aio_connections);
    tl_create_aio_query (aio_connections[i], &Connections[0], timeout, &default_tl_aio_metafile_query_type, q);
  }
  q->wait_num += conn_num;
  vkprintf (1, "Creating aio for rpc\n");
  return q->wait_num;
}