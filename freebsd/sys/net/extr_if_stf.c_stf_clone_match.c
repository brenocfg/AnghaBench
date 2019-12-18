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
 int /*<<< orphan*/ ** stfnames ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
stf_clone_match(struct if_clone *ifc, const char *name)
{
	int i;

	for(i = 0; stfnames[i] != NULL; i++) {
		if (strcmp(stfnames[i], name) == 0)
			return (1);
	}

	return (0);
}