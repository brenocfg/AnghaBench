#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_server {scalar_t__ packet_num; scalar_t__ sfd; } ;
struct rpc_connection {int default_actor_id; int /*<<< orphan*/  servers; } ;
struct TYPE_4__ {scalar_t__ rptr; scalar_t__ sptr; int wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int (*) (struct rpc_connection*,long long,double)) ; 
 int /*<<< orphan*/  END_TIMER (int (*) (struct rpc_connection*,long long,double)) ; 
 int RPC_INVOKE_REQ ; 
 int /*<<< orphan*/  START_TIMER (int (*) (struct rpc_connection*,long long,double)) ; 
 int TL_RPC_DEST_ACTOR ; 
 int TL_RPC_DEST_ACTOR_FLAGS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_write_int (TYPE_1__*,unsigned int) ; 
 struct rpc_server* choose_writable_server (int /*<<< orphan*/ ,double) ; 
 TYPE_1__* outbuf ; 
 int /*<<< orphan*/  rpc_server_failure (struct rpc_server*) ; 
 scalar_t__ rpc_write_out (struct rpc_server*,int,int,double) ; 

__attribute__((used)) static int rpc_write (struct rpc_connection *c, long long qid, double timeout) { /* {{{ */
  ADD_CNT (rpc_write);
  START_TIMER (rpc_write);
//  struct rpc_server *server = c->server;
  struct rpc_server *server = choose_writable_server (c->servers, timeout);
  if (!server) {
    END_TIMER (rpc_write);
    return -1;
  }
  assert (qid && server->packet_num >= 0);

  if (server->sfd < 0) {
    END_TIMER (rpc_write);
    return -1;
  }

  if (!outbuf) {
    END_TIMER (rpc_write);
    return -1;
  }

  if (c->default_actor_id) {
    int x = *(int *)outbuf->rptr;
    if (x != TL_RPC_DEST_ACTOR && x != TL_RPC_DEST_ACTOR_FLAGS) {
      outbuf->rptr -= 12;
      assert (outbuf->rptr >= outbuf->sptr);
      *(int *)outbuf->rptr = TL_RPC_DEST_ACTOR;
      *(long long *)(outbuf->rptr + 4) = c->default_actor_id;
    }
  }
  int len = 24 + (outbuf->wptr - outbuf->rptr);
  unsigned crc32 = 0;
  outbuf->rptr -= 20;
  assert (outbuf->rptr >= outbuf->sptr);
  int *tmp = (void *)outbuf->rptr;
  tmp[0] = len;
  tmp[1] = server->packet_num ++;
  tmp[2] = RPC_INVOKE_REQ;
  *(long long *)(tmp + 3) = qid;
#ifdef SEND_CRC32
  ADD_CNT (crc32);
  START_TICKS (crc32);
  crc32 = compute_crc32 (outbuf->rptr, outbuf->wptr - outbuf->rptr);
  END_TICKS (crc32);
#endif
  buffer_write_int (outbuf, crc32);
  assert (outbuf->wptr - outbuf->rptr == len);
  
  if (rpc_write_out (server, outbuf->rptr, len, timeout) < 0) {
    rpc_server_failure (server);
    END_TIMER (rpc_write);
    return -1;
  }
  buffer_clear (outbuf);
  END_TIMER (rpc_write);
  return 0;
}