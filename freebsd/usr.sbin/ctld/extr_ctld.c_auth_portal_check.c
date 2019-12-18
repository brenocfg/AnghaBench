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
struct sockaddr_storage {int dummy; } ;
struct auth_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_portal_defined (struct auth_group const*) ; 
 int /*<<< orphan*/ * auth_portal_find (struct auth_group const*,struct sockaddr_storage const*) ; 

int
auth_portal_check(const struct auth_group *ag, const struct sockaddr_storage *sa)
{

	if (!auth_portal_defined(ag))
		return (0);

	if (auth_portal_find(ag, sa) == NULL)
		return (1);

	return (0);
}