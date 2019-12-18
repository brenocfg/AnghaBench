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
 int /*<<< orphan*/  rmdir (char const*) ; 
 int warn_if_unremovable (char*,char const*,int /*<<< orphan*/ ) ; 

int rmdir_or_warn(const char *file)
{
	return warn_if_unremovable("rmdir", file, rmdir(file));
}