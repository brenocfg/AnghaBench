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
struct rpc_server {int in_bytes; scalar_t__ in_pos; scalar_t__ in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  read_in ; 

__attribute__((used)) static int rpc_read_in (struct rpc_server *server, char *data, int len, double timeout) {
  ADD_CNT (read_in);
  START_TIMER (read_in);
  if (len <= server->in_bytes) {
    memcpy (data, server->in_buf + server->in_pos, len);
    server->in_pos += len;
    server->in_bytes -= len;
    END_TIMER (read_in);
    return len;
  } else {    
    memcpy (data, server->in_buf + server->in_pos, server->in_bytes);
    int t = server->in_bytes;
    server->in_pos = 0;
    server->in_bytes = 0;
    END_TIMER (read_in);
    return t;
  }
}