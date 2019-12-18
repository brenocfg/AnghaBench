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
struct varlist {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int MAXLIST ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct varlist *
findlistvar(
	struct varlist *list,
	char *name
	)
{
	struct varlist *vl;

	for (vl = list; vl < list + MAXLIST && vl->name != NULL; vl++)
		if (!strcmp(name, vl->name))
			return vl;
	if (vl < list + MAXLIST)
		return vl;

	return NULL;
}