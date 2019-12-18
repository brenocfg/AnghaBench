#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct ssh {int dummy; } ;
struct TYPE_9__ {struct TYPE_9__* val; struct TYPE_9__* name; } ;
struct TYPE_8__ {int ttyfd; size_t num_env; int /*<<< orphan*/  self; TYPE_6__* env; TYPE_6__* subsys; TYPE_6__* auth_proto; TYPE_6__* auth_data; TYPE_6__* auth_display; TYPE_6__* x11_chanids; TYPE_6__* display; TYPE_6__* term; TYPE_1__* pw; } ;
struct TYPE_7__ {int /*<<< orphan*/  pw_name; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 int /*<<< orphan*/  session_proctitle (TYPE_2__*) ; 
 int /*<<< orphan*/  session_pty_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  session_unused (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
session_close(struct ssh *ssh, Session *s)
{
	u_int i;

	verbose("Close session: user %s from %.200s port %d id %d",
	    s->pw->pw_name,
	    ssh_remote_ipaddr(ssh),
	    ssh_remote_port(ssh),
	    s->self);

	if (s->ttyfd != -1)
		session_pty_cleanup(s);
	free(s->term);
	free(s->display);
	free(s->x11_chanids);
	free(s->auth_display);
	free(s->auth_data);
	free(s->auth_proto);
	free(s->subsys);
	if (s->env != NULL) {
		for (i = 0; i < s->num_env; i++) {
			free(s->env[i].name);
			free(s->env[i].val);
		}
		free(s->env);
	}
	session_proctitle(s);
	session_unused(s->self);
}