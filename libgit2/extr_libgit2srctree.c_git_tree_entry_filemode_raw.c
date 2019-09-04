#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
typedef  TYPE_1__ git_tree_entry ;
typedef  int /*<<< orphan*/  git_filemode_t ;

/* Variables and functions */

git_filemode_t git_tree_entry_filemode_raw(const git_tree_entry *entry)
{
	return entry->attr;
}