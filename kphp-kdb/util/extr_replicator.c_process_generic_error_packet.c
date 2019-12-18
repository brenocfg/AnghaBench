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
struct repl_error {int /*<<< orphan*/  error; int /*<<< orphan*/  session_id; int /*<<< orphan*/  handshake_id; int /*<<< orphan*/  error_message; } ;
struct connection {int /*<<< orphan*/  remote_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  bad_error_packet (struct repl_error*,int) ; 
 int /*<<< orphan*/  errors_received ; 
 int /*<<< orphan*/  show_remote_ip (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int process_generic_error_packet (struct connection *c, struct repl_error *E, int len) {
  errors_received++;
  if (!bad_error_packet (E, len)) {
    vkprintf (0, "Received error packet in session %d:%d from %s:%d, error code %d: %s\n", E->handshake_id, E->session_id, show_remote_ip (c),
	      c->remote_port, E->error, E->error_message);
  } else {
    vkprintf (0, "Received malformed error packet in session %d:%d from %s:%d, error code %d\n", E->handshake_id, E->session_id, show_remote_ip (c),
	      c->remote_port, E->error);
  }
  return 0;
}