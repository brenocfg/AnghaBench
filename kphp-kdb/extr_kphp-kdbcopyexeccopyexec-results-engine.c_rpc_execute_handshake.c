#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct copyexec_rpc_pos {int /*<<< orphan*/  binlog_pos; } ;
struct copyexec_rpc_handshake_error {int error_code; } ;
struct copyexec_rpc_handshake {int hostname_length; char* hostname; int /*<<< orphan*/  random_tag; int /*<<< orphan*/  volume_id; int /*<<< orphan*/  pid; } ;
struct connection {int /*<<< orphan*/  remote_ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  binlog_pos; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPYEXEC_RPC_TYPE_ERR_HANDSHAKE ; 
 int /*<<< orphan*/  COPYEXEC_RPC_TYPE_VALUE_POS ; 
 int /*<<< orphan*/  Q ; 
 int /*<<< orphan*/  copyexec_strerror (int) ; 
 int do_connect (struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 void* rpc_create_query (int /*<<< orphan*/ ,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (int /*<<< orphan*/ ,struct connection*) ; 
 int /*<<< orphan*/  show_ip (int /*<<< orphan*/ ) ; 

int rpc_execute_handshake (struct connection *c, struct copyexec_rpc_handshake *P, int len) {
  int sz = sizeof (struct copyexec_rpc_handshake);
  if (len < sz) {
    return -__LINE__;
  }
  int l = P->hostname_length;
  sz += l;
  sz = (sz + 3) & -4;
  if (len != sz) {
    return -__LINE__;
  }

  host_t *H;
  char ch = P->hostname[l];
  P->hostname[l] = 0; /* possibly broke packet crc32 */
  int r = do_connect (c, P->volume_id, P->random_tag, P->hostname, P->pid, &H);
  P->hostname[l] = ch; /* restore packet crc32 */

  if (r < 0) {
    kprintf ("rpc_execute_handshake: do_connect (c->remote_ip: %s, volume_id: 0x%llx, random_tag: 0x%llx, hostname: %.*s) returns %s.\n",
      show_ip (c->remote_ip), P->volume_id, P->random_tag, P->hostname_length, P->hostname, copyexec_strerror (r));
    struct copyexec_rpc_handshake_error *E = rpc_create_query (Q, sizeof (*E), c, COPYEXEC_RPC_TYPE_ERR_HANDSHAKE);
    if (E == NULL) {
      return -__LINE__;
    }
    E->error_code = r;
    return rpc_send_query (Q, c);
  }

  struct copyexec_rpc_pos *E = rpc_create_query (Q, sizeof (*E), c, COPYEXEC_RPC_TYPE_VALUE_POS);
  if (E == NULL) {
    return -__LINE__;
  }
  E->binlog_pos = H->binlog_pos;

  return rpc_send_query (Q, c);
}