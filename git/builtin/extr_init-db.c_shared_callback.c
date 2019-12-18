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
struct option {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int PERM_GROUP ; 
 int git_config_perm (char*,char const*) ; 

__attribute__((used)) static int shared_callback(const struct option *opt, const char *arg, int unset)
{
	BUG_ON_OPT_NEG(unset);
	*((int *) opt->value) = (arg) ? git_config_perm("arg", arg) : PERM_GROUP;
	return 0;
}