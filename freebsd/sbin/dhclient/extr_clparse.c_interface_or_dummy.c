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
struct interface_info {struct interface_info* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 struct interface_info* dummy_interfaces ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct interface_info* ifi ; 
 struct interface_info* malloc (int) ; 
 int /*<<< orphan*/  memset (struct interface_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct interface_info *
interface_or_dummy(char *name)
{
	struct interface_info	*ip;

	/* Find the interface (if any) that matches the name. */
	if (!strcmp(ifi->name, name))
		return (ifi);

	/* If it's not a real interface, see if it's on the dummy list. */
	for (ip = dummy_interfaces; ip; ip = ip->next)
		if (!strcmp(ip->name, name))
			return (ip);

	/*
	 * If we didn't find an interface, make a dummy interface as a
	 * placeholder.
	 */
	ip = malloc(sizeof(*ip));
	if (!ip)
		error("Insufficient memory to record interface %s", name);
	memset(ip, 0, sizeof(*ip));
	strlcpy(ip->name, name, IFNAMSIZ);
	ip->next = dummy_interfaces;
	dummy_interfaces = ip;
	return (ip);
}