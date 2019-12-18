#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ value; } ;
typedef  TYPE_1__ svn_sort__item_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ svn_fs_dirent_t ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_dir_entries_format7(const svn_sort__item_t *a,
                            const svn_sort__item_t *b)
{
  const svn_fs_dirent_t *lhs = (const svn_fs_dirent_t *) a->value;
  const svn_fs_dirent_t *rhs = (const svn_fs_dirent_t *) b->value;

  return strcmp(lhs->name, rhs->name);
}