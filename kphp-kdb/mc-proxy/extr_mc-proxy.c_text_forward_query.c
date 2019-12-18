#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connection {int fd; int /*<<< orphan*/  Out; int /*<<< orphan*/  query_start_time; } ;
struct conn_target {int dummy; } ;
struct conn_query {int custom_type; } ;
struct TYPE_6__ {int tot_buckets; int step; int cluster_mode; int a_req; int a_sbytes; int t_req; int t_sbytes; TYPE_1__* listening_connection; int /*<<< orphan*/  set_timeout; struct conn_target** buckets; } ;
struct TYPE_5__ {int query_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  generation; int /*<<< orphan*/  query_start_time; } ;

/* Variables and functions */
 TYPE_3__* CC ; 
 int CLUSTER_MODE_FIRSTINT ; 
 int MAX_USER_FRIENDS ; 
 TYPE_2__* MCS_DATA (struct connection*) ; 
 size_t* RR ; 
 int /*<<< orphan*/  assert (int) ; 
 struct conn_query* create_query (struct connection*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int diagonal_forwarded_total ; 
 int /*<<< orphan*/  diagonal_received_queries ; 
 int /*<<< orphan*/  flush_output (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct connection* get_target_connection (struct conn_target*) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ursort (int*,int /*<<< orphan*/ ,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,...) ; 

int text_forward_query (char *key, int key_len, int N, int *A, struct connection *c) {
  int i, tb = CC->tot_buckets, j, res = 0, k, st = CC->step > 0 ? CC->step : 1, cur_forwarded_queries = 0, cur_forwarded_bytes = 0;
  struct connection *d;
  struct conn_query *Q;
  struct conn_target *S;

  if (verbosity > 0) {
    fprintf (stderr, "in text_forward_query(%s, %d, %d; %d %d %d)\n", key, c->fd, N, A[0], A[1], A[2]);
  }

  ++diagonal_received_queries;

  if (N <= 0 || N >= MAX_USER_FRIENDS || !tb || (CC->cluster_mode & 255) != CLUSTER_MODE_FIRSTINT) {
    return 0;
  }
  assert (A && key);
  for (i = 0; i < N; i++) {
    RR[i] = (A[i] / st) % tb;
  }

  CC->listening_connection->query_start_time = c->query_start_time;

  ursort (A, 0, N - 1);
  RR[N] = tb;
  j = 0;
  for (i = 1; i <= N; i++) {
    if (RR[i] != RR[i - 1]) {
      if (RR[j] >= 0) {
        A[j - 1] = i - j;
        S = CC->buckets[RR[j]];
        d = get_target_connection (S);
        if (d) {
          Q = create_query (d, CC->listening_connection, CC->set_timeout);
          Q->custom_type = MCS_DATA(c)->query_type | 0x2000;

          if (verbosity > 1) {
            fprintf (stderr, "Forwarded online friends list (key = %s) to bucket %d:", key, RR[j]);
            for (k = j - 1; k < i; k++) {
              fprintf (stderr, " %d", A[k]);
            }
            fprintf (stderr, "\n");
          }

          static char sm_buff[32];
          int l = sprintf (sm_buff, " 0 0 %d\r\n", (i - j + 1) * 4);

          write_out (&d->Out, "set ", 4);
          write_out (&d->Out, key, key_len);
          write_out (&d->Out, sm_buff, l);
          write_out (&d->Out, A + (j - 1), (i - j + 1) * 4);
          write_out (&d->Out, "\r\n", 2);

	  cur_forwarded_queries++;
	  cur_forwarded_bytes += 4 + key_len + l + (i - j + 1) * 4 + 2;

          res += i - j;

          flush_output (d);
        }
      }
      j = i;
    }
  }

  if (res) {
    CC->a_req += cur_forwarded_queries;
    CC->a_sbytes += cur_forwarded_bytes;
    CC->t_req += cur_forwarded_queries;
    CC->t_sbytes += cur_forwarded_bytes;
    diagonal_forwarded_total += res;
    CC->listening_connection->generation++;
  }

  return res;
}