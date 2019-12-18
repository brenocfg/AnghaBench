#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pdu {int dummy; } ;
struct connection {TYPE_3__* conn_target; TYPE_2__* conn_portal; } ;
struct TYPE_6__ {char* t_redirection; int /*<<< orphan*/  t_name; } ;
struct TYPE_5__ {TYPE_1__* p_portal_group; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pg_redirection; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debugx (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  login_redirect (struct pdu*,char const*) ; 

__attribute__((used)) static bool
login_target_redirect(struct connection *conn, struct pdu *request)
{
	const char *target_address;

	assert(conn->conn_portal->p_portal_group->pg_redirection == NULL);

	if (conn->conn_target == NULL)
		return (false);

	target_address = conn->conn_target->t_redirection;
	if (target_address == NULL)
		return (false);

	log_debugx("target \"%s\" configured to redirect to %s",
	  conn->conn_target->t_name, target_address);
	login_redirect(request, target_address);

	return (true);
}