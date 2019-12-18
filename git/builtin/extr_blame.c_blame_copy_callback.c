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
struct option {int* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int PICKAXE_BLAME_COPY ; 
 int PICKAXE_BLAME_COPY_HARDER ; 
 int PICKAXE_BLAME_COPY_HARDEST ; 
 int PICKAXE_BLAME_MOVE ; 
 int /*<<< orphan*/  blame_copy_score ; 
 int /*<<< orphan*/  parse_score (char const*) ; 

__attribute__((used)) static int blame_copy_callback(const struct option *option, const char *arg, int unset)
{
	int *opt = option->value;

	BUG_ON_OPT_NEG(unset);

	/*
	 * -C enables copy from removed files;
	 * -C -C enables copy from existing files, but only
	 *       when blaming a new file;
	 * -C -C -C enables copy from existing files for
	 *          everybody
	 */
	if (*opt & PICKAXE_BLAME_COPY_HARDER)
		*opt |= PICKAXE_BLAME_COPY_HARDEST;
	if (*opt & PICKAXE_BLAME_COPY)
		*opt |= PICKAXE_BLAME_COPY_HARDER;
	*opt |= PICKAXE_BLAME_COPY | PICKAXE_BLAME_MOVE;

	if (arg)
		blame_copy_score = parse_score(arg);
	return 0;
}