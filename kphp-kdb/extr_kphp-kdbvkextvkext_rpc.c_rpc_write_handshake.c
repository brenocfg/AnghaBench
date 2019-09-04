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
struct rpc_server {int packet_num; scalar_t__ sfd; } ;
struct TYPE_4__ {int wptr; int rptr; scalar_t__ sptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int (*) (struct rpc_server*,int,double)) ; 
 int /*<<< orphan*/  END_TIMER (int (*) (struct rpc_server*,int,double)) ; 
 int RPC_HANDSHAKE ; 
 int RPC_NONCE ; 
 int RPC_PING ; 
 int /*<<< orphan*/  START_TIMER (int (*) (struct rpc_server*,int,double)) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_write_int (TYPE_1__*,unsigned int) ; 
 TYPE_1__* outbuf ; 
 scalar_t__ rpc_write_out (struct rpc_server*,int,int,double) ; 

__attribute__((used)) static int rpc_write_handshake (struct rpc_server *server, int op, double timeout) { /* {{{ */
  ADD_CNT (rpc_write_handshake);
  START_TIMER (rpc_write_handshake);
  assert (op == RPC_NONCE || op == RPC_HANDSHAKE || op == RPC_PING);
  if (op == RPC_NONCE && server->packet_num != -2) {
    assert (0);
  }
  if (op == RPC_HANDSHAKE && server->packet_num != -1) {
    assert (0);
  }
  if (op == RPC_PING && server->packet_num < 0) {
    assert (0);
  }
  if (server->sfd < 0) {
    END_TIMER (rpc_write_handshake);
    return -1;
  }
  if (!outbuf) {
    END_TIMER (rpc_write_handshake);
    return -1;
  }
  int len = 16 + (outbuf->wptr - outbuf->rptr);
  unsigned crc32 = 0;

  outbuf->rptr -= 12;
  assert (outbuf->rptr >= outbuf->sptr);
  int *tmp = (void *)outbuf->rptr;
  tmp[0] = len;
  tmp[1] = server->packet_num ++;
  tmp[2] = op;
#ifdef SEND_CRC32
  ADD_CNT (crc32);
  START_TICKS (crc32);
  crc32 = compute_crc32 (outbuf->rptr, outbuf->wptr - outbuf->rptr);
  END_TICKS (crc32);
#endif
  buffer_write_int (outbuf, crc32);
  assert (outbuf->wptr - outbuf->rptr == len);
  
  if (rpc_write_out (server, outbuf->rptr, len, timeout) < 0) {
    END_TIMER (rpc_write_handshake);
    return -1;
  }
  buffer_clear (outbuf);
  END_TIMER (rpc_write_handshake);
  return 0;

}