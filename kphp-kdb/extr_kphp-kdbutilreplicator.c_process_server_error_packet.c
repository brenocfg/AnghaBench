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
struct repl_server_status {int dummy; } ;
struct repl_error {int /*<<< orphan*/  session_id; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_server (struct repl_server_status*) ; 
 struct repl_server_status* get_server_by_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int process_generic_error_packet (struct connection*,struct repl_error*,int) ; 

int process_server_error_packet (struct connection *c, struct repl_error *E, int len) {
  struct repl_server_status *S = get_server_by_session (E->session_id, 0);
  if (S) {
    destroy_server (S);
  }
  return process_generic_error_packet (c, E, len);
}