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
typedef  int /*<<< orphan*/  git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_DEC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attr_file_free ; 

void git_attr_file__free(git_attr_file *file)
{
	if (!file)
		return;
	GIT_REFCOUNT_DEC(file, attr_file_free);
}