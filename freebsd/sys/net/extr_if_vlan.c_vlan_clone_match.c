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
struct if_clone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlan_clone_match_ethervid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlanname ; 

__attribute__((used)) static int
vlan_clone_match(struct if_clone *ifc, const char *name)
{
	const char *cp;

	if (vlan_clone_match_ethervid(name, NULL) != NULL)
		return (1);

	if (strncmp(vlanname, name, strlen(vlanname)) != 0)
		return (0);
	for (cp = name + 4; *cp != '\0'; cp++) {
		if (*cp < '0' || *cp > '9')
			return (0);
	}

	return (1);
}