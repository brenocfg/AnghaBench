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
struct servtab {scalar_t__ se_policy; scalar_t__* se_argv; scalar_t__ se_pids; scalar_t__ se_server; scalar_t__ se_class; scalar_t__ se_group; scalar_t__ se_user; scalar_t__ se_proto; scalar_t__ se_service; } ;

/* Variables and functions */
 int MAXARGV ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_connlist (struct servtab*) ; 

__attribute__((used)) static void
freeconfig(struct servtab *cp)
{
	int i;

	if (cp->se_service)
		free(cp->se_service);
	if (cp->se_proto)
		free(cp->se_proto);
	if (cp->se_user)
		free(cp->se_user);
	if (cp->se_group)
		free(cp->se_group);
#ifdef LOGIN_CAP
	if (cp->se_class)
		free(cp->se_class);
#endif
	if (cp->se_server)
		free(cp->se_server);
	if (cp->se_pids)
		free(cp->se_pids);
	for (i = 0; i < MAXARGV; i++)
		if (cp->se_argv[i])
			free(cp->se_argv[i]);
	free_connlist(cp);
#ifdef IPSEC
	if (cp->se_policy)
		free(cp->se_policy);
#endif
}