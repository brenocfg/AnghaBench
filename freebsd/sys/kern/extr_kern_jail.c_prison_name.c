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
struct prison {char* pr_name; struct prison* pr_parent; } ;

/* Variables and functions */
 struct prison prison0 ; 
 scalar_t__ prison_ischild (struct prison*,struct prison*) ; 
 char* strchr (char*,char) ; 

char *
prison_name(struct prison *pr1, struct prison *pr2)
{
	char *name;

	/* Jails see themselves as "0" (if they see themselves at all). */
	if (pr1 == pr2)
		return "0";
	name = pr2->pr_name;
	if (prison_ischild(pr1, pr2)) {
		/*
		 * pr1 isn't locked (and allprison_lock may not be either)
		 * so its length can't be counted on.  But the number of dots
		 * can be counted on - and counted.
		 */
		for (; pr1 != &prison0; pr1 = pr1->pr_parent)
			name = strchr(name, '.') + 1;
	}
	return (name);
}