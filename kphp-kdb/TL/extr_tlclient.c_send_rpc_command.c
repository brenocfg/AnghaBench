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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * P ; 
 int PACKET_BUFFER_SIZE ; 
 int additional ; 
 int /*<<< orphan*/  compiler ; 
 int /*<<< orphan*/  exit (int) ; 
 struct connection* get_target_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  log_errors () ; 
 int /*<<< orphan*/  log_str (char*) ; 
 int /*<<< orphan*/  rpcc_send_query (struct connection*,int) ; 
 int /*<<< orphan*/  targ ; 
 int /*<<< orphan*/  tl_compiler_clear_errors (int /*<<< orphan*/ *) ; 
 int tl_serialize_rpc_function_call (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typename ; 

int send_rpc_command (char *cmd) {
  tl_compiler_clear_errors (&compiler);
  int r = tl_serialize_rpc_function_call (&compiler, cmd, &P[5 + additional], PACKET_BUFFER_SIZE - 6 - additional, &typename);
  if (r < 0) {
    log_str ("tl_serialize_rpc_function_call fail. Errors:\n");
    log_errors ();
    return r;
  } else {
    struct connection *c = get_target_connection (targ);
    if (c == NULL) {
      kprintf ("get_target_connection returns NULL.\n");
      exit (1);
    }
    rpcc_send_query (c, r);
  }
  return 0;
}