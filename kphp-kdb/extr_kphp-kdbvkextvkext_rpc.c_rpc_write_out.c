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
struct rpc_server {scalar_t__ sfd; int out_bytes; scalar_t__ out_rptr; scalar_t__ out_wptr; scalar_t__ out_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int RPC_OUT_BUF_SIZE ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 
 int /*<<< orphan*/  rpc_server_failure (struct rpc_server*) ; 
 int /*<<< orphan*/  rpc_server_seterror (struct rpc_server*,char*,int /*<<< orphan*/ ) ; 
 int rpc_sock_write (struct rpc_server*,double,char*,int,int) ; 
 int /*<<< orphan*/  write_out ; 

__attribute__((used)) static int rpc_write_out (struct rpc_server *server, char *data, int len, double timeout) {
  if (server->sfd < 0) {
    return -1;
  }
  if (!len) {
    return 0;
  }
  int _len = len;
  ADD_CNT (write_out);
  START_TIMER (write_out);  
  int x = server->out_bytes;
  if (x + len >= RPC_OUT_BUF_SIZE) {
    int r = rpc_sock_write (server, timeout, data, len, x + len - RPC_OUT_BUF_SIZE + 1024);
    if (r < 0) {
      END_TIMER (write_out);
      return -1;
    }
    if (r > x) {
      data += (r - x);
      len -= (r - x);
    }
    x = server->out_bytes;
    if (x + len >= RPC_OUT_BUF_SIZE) {
      rpc_server_seterror (server, "Write timeout", 0);
      rpc_server_failure (server);
      END_TIMER (write_out);
      return -1;
    }
  }
  server->out_bytes += len;
  if (server->out_rptr <= server->out_wptr) {
    if (server->out_wptr + len <= server->out_buf + RPC_OUT_BUF_SIZE) {
      memcpy (server->out_wptr, data, len);
      server->out_wptr += len;
      END_TIMER (write_out);
      return _len;
    } else {
      int q = server->out_buf + RPC_OUT_BUF_SIZE - server->out_wptr;
      memcpy (server->out_wptr, data, q);
      memcpy (server->out_buf, data + q, len - q);
      server->out_wptr = server->out_buf + (len - q);
      END_TIMER (write_out);
      return _len;
    }
  } else {
    memcpy (server->out_wptr, data, len);
    server->out_wptr += len;
    END_TIMER (write_out);
    return _len;
  }
}