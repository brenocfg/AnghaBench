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
struct branch {int dummy; } ;

/* Variables and functions */
 struct branch* current_branch ; 
 struct branch* make_branch (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_config () ; 
 int /*<<< orphan*/  set_merge (struct branch*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

struct branch *branch_get(const char *name)
{
	struct branch *ret;

	read_config();
	if (!name || !*name || !strcmp(name, "HEAD"))
		ret = current_branch;
	else
		ret = make_branch(name, 0);
	set_merge(ret);
	return ret;
}