#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xpid ;
struct TYPE_2__ {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct rpcs_data {int /*<<< orphan*/ * extra; TYPE_1__ remote_pid; } ;
struct connection {int /*<<< orphan*/  status; int /*<<< orphan*/  pending_queries; int /*<<< orphan*/  In; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  rpc_query_data ;
typedef  int /*<<< orphan*/  php_worker ;
typedef  int /*<<< orphan*/  npid_t ;

/* Variables and functions */
 int MAX_RPC_QUERY_LEN ; 
 struct rpcs_data* RPCS_DATA (struct connection*) ; 
#define  RPC_INVOKE_KPHP_REQ 131 
#define  RPC_INVOKE_REQ 130 
 int SKIP_ALL_BYTES ; 
#define  TL_KPHP_START_LEASE 129 
#define  TL_KPHP_STOP_LEASE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  conn_wait_net ; 
 int /*<<< orphan*/  do_rpc_start_lease (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  do_rpc_stop_lease () ; 
 int /*<<< orphan*/  once_worker ; 
 int /*<<< orphan*/ * php_worker_create (int /*<<< orphan*/ ,struct connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long long) ; 
 int php_worker_main (int /*<<< orphan*/ *) ; 
 scalar_t__ precise_now ; 
 int read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * rpc_query_data_create (int*,int,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_worker ; 
 int /*<<< orphan*/  rpcx_at_query_end (struct connection*) ; 
 int /*<<< orphan*/  run_once ; 
 int /*<<< orphan*/  script_timeout ; 
 int /*<<< orphan*/  set_connection_timeout (struct connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ sigterm_on ; 
 scalar_t__ sigterm_time ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,...) ; 

int rpcx_execute (struct connection *c, int op, int len) {
  struct rpcs_data *D = RPCS_DATA(c);

  vkprintf (1, "rpcs_execute: fd=%d, op=%d, len=%d\n", c->fd, op, len);

#define MAX_RPC_QUERY_LEN 126214400
  static char buf[MAX_RPC_QUERY_LEN];

  if (sigterm_on && sigterm_time < precise_now) {
    return SKIP_ALL_BYTES;
  }
  npid_t xpid;

  switch (op) {
  case TL_KPHP_STOP_LEASE:
    do_rpc_stop_lease();
    break;
  case TL_KPHP_START_LEASE:
  case RPC_INVOKE_KPHP_REQ:
  case RPC_INVOKE_REQ:
    if (len > MAX_RPC_QUERY_LEN) {
      return SKIP_ALL_BYTES;
    }

    assert (read_in (&c->In, buf, len) == len);
    assert (len % (int)sizeof (int) == 0);
    len /= (int)sizeof (int);
    if (len < 6) {
      return SKIP_ALL_BYTES;
    }

    int *v = (int *)buf;
    v += 3;
    len -= 4;

    if (op == TL_KPHP_START_LEASE) {
      if (len < 4) {
        return SKIP_ALL_BYTES;
      }
      assert (sizeof (xpid) == 12);
      xpid = *(npid_t *)v;
      v += 3;
      len -= 3;
      int timeout = *v++;
      len--;
      do_rpc_start_lease (xpid, precise_now + timeout);
      return 0;
      break;
    }

    long long req_id = *(long long *)v;
    v += 2;
    len -= 2;

    vkprintf (2, "got RPC_INVOKE_KPHP_REQ [req_id = %016llx]\n", req_id);
    set_connection_timeout (c, script_timeout);


    rpc_query_data *rpc_data = rpc_query_data_create (v, len, req_id, D->remote_pid.ip, D->remote_pid.port, D->remote_pid.pid, D->remote_pid.utime);

    php_worker *worker = php_worker_create (run_once ? once_worker : rpc_worker, c, NULL, rpc_data, script_timeout, req_id);
    D->extra = worker;

    int res = php_worker_main (worker);
    if (res == 1) {
      rpcx_at_query_end (c);
    } else {
      assert (c->pending_queries >= 0 && c->status == conn_wait_net);
    }

    return 0;
    break;
  }

  return SKIP_ALL_BYTES;
#undef MAX_RPC_QUERY_LEN
}