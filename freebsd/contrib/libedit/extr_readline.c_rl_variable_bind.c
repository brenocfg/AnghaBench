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
 int /*<<< orphan*/  EL_BIND ; 
 int /*<<< orphan*/  e ; 
 int el_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ *) ; 

int
rl_variable_bind(const char *var, const char *value)
{
	/*
	 * The proper return value is undocument, but this is what the
	 * readline source seems to do.
	 */
	return el_set(e, EL_BIND, "", var, value, NULL) == -1 ? 1 : 0;
}