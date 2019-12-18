#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct portal_group {int /*<<< orphan*/ * pg_redirection; int /*<<< orphan*/  pg_name; } ;
struct pdu {int dummy; } ;
struct connection {TYPE_1__* conn_portal; } ;
struct TYPE_2__ {struct portal_group* p_portal_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debugx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  login_redirect (struct pdu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
login_portal_redirect(struct connection *conn, struct pdu *request)
{
	const struct portal_group *pg;

	pg = conn->conn_portal->p_portal_group;
	if (pg->pg_redirection == NULL)
		return (false);

	log_debugx("portal-group \"%s\" configured to redirect to %s",
	    pg->pg_name, pg->pg_redirection);
	login_redirect(request, pg->pg_redirection);

	return (true);
}