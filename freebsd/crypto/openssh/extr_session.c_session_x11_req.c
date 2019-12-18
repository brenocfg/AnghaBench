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
struct ssh {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * auth_data; int /*<<< orphan*/ * auth_proto; int /*<<< orphan*/  screen; int /*<<< orphan*/  single_connection; int /*<<< orphan*/  self; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_check_eom () ; 
 int /*<<< orphan*/  packet_get_char () ; 
 int /*<<< orphan*/  packet_get_int () ; 
 void* packet_get_string (int /*<<< orphan*/ *) ; 
 int session_setup_x11fwd (struct ssh*,TYPE_1__*) ; 
 scalar_t__ xauth_valid_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
session_x11_req(struct ssh *ssh, Session *s)
{
	int success;

	if (s->auth_proto != NULL || s->auth_data != NULL) {
		error("session_x11_req: session %d: "
		    "x11 forwarding already active", s->self);
		return 0;
	}
	s->single_connection = packet_get_char();
	s->auth_proto = packet_get_string(NULL);
	s->auth_data = packet_get_string(NULL);
	s->screen = packet_get_int();
	packet_check_eom();

	if (xauth_valid_string(s->auth_proto) &&
	    xauth_valid_string(s->auth_data))
		success = session_setup_x11fwd(ssh, s);
	else {
		success = 0;
		error("Invalid X11 forwarding data");
	}
	if (!success) {
		free(s->auth_proto);
		free(s->auth_data);
		s->auth_proto = NULL;
		s->auth_data = NULL;
	}
	return success;
}