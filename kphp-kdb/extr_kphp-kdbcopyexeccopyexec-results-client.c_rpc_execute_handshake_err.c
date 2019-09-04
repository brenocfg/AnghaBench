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
struct copyexec_rpc_handshake_error {int /*<<< orphan*/  error_code; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_state_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cur_client_state ; 
 scalar_t__ handshake_sent_time ; 
 int /*<<< orphan*/  kprintf (char*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ now ; 

int rpc_execute_handshake_err (struct connection *c, struct copyexec_rpc_handshake_error *P, int len) {
  if (len != sizeof (struct copyexec_rpc_handshake_error)) {
    return -__LINE__;
  }
  kprintf ("rpc_execute_handshake_err (c: %p, P->error_code: %d). cur_client_state: %s\n", c, P->error_code, client_state_to_str (cur_client_state));
  handshake_sent_time = now + 10 * 60; /* send handshake packet again ~10 minutes latter */
  return 0;
}