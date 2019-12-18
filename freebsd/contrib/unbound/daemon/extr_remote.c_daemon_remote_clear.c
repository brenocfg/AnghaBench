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
struct rc_state {int /*<<< orphan*/  c; scalar_t__ ssl; struct rc_state* next; } ;
struct daemon_remote {int /*<<< orphan*/ * worker; scalar_t__ active; struct rc_state* busy_list; int /*<<< orphan*/ * accept_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_free (scalar_t__) ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rc_state*) ; 
 int /*<<< orphan*/  listen_list_delete (int /*<<< orphan*/ *) ; 

void daemon_remote_clear(struct daemon_remote* rc)
{
	struct rc_state* p, *np;
	if(!rc) return;
	/* but do not close the ports */
	listen_list_delete(rc->accept_list);
	rc->accept_list = NULL;
	/* do close these sockets */
	p = rc->busy_list;
	while(p) {
		np = p->next;
		if(p->ssl)
			SSL_free(p->ssl);
		comm_point_delete(p->c);
		free(p);
		p = np;
	}
	rc->busy_list = NULL;
	rc->active = 0;
	rc->worker = NULL;
}