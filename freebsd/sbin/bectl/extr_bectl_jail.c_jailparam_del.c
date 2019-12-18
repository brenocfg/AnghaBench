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

/* Variables and functions */
 int /*<<< orphan*/  jailparams ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
jailparam_del(const char *name)
{

	nvlist_remove_all(jailparams, name);
	return (0);
}