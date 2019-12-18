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
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int git_odb__add_default_backends (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

int git_odb_add_disk_alternate(git_odb *odb, const char *path)
{
	return git_odb__add_default_backends(odb, path, true, 0);
}