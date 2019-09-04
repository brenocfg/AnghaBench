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
struct stat {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int add_to_index (struct index_state*,char const*,struct stat*,int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 

int add_file_to_index(struct index_state *istate, const char *path, int flags)
{
	struct stat st;
	if (lstat(path, &st))
		die_errno(_("unable to stat '%s'"), path);
	return add_to_index(istate, path, &st, flags);
}