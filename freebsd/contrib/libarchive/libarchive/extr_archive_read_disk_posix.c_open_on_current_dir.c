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
struct tree {int dummy; } ;

/* Variables and functions */
 int open (char const*,int) ; 
 int openat (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  tree_current_dir_fd (struct tree*) ; 
 scalar_t__ tree_enter_working_dir (struct tree*) ; 

__attribute__((used)) static int
open_on_current_dir(struct tree *t, const char *path, int flags)
{
#ifdef HAVE_OPENAT
	return (openat(tree_current_dir_fd(t), path, flags));
#else
	if (tree_enter_working_dir(t) != 0)
		return (-1);
	return (open(path, flags));
#endif
}