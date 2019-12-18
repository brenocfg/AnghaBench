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
struct cfjail {int dummy; } ;

/* Variables and functions */
 struct cfjail** bsearch (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_jailptr_name ; 
 int /*<<< orphan*/ * jails_byname ; 
 int /*<<< orphan*/  njails ; 

__attribute__((used)) static struct cfjail *
find_jail(const char *name)
{
	struct cfjail **jp;
	
	if (jails_byname == NULL)
		return NULL;

	jp = bsearch(name, jails_byname, njails, sizeof(struct cfjail *),
	    cmp_jailptr_name);
	return jp ? *jp : NULL;
}