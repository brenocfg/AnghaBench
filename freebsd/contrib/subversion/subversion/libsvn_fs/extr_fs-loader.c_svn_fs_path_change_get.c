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
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_path_change_iterator_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* get ) (int /*<<< orphan*/ **,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ **,TYPE_2__*) ; 

svn_error_t *
svn_fs_path_change_get(svn_fs_path_change3_t **change,
                       svn_fs_path_change_iterator_t *iterator)
{
  return iterator->vtable->get(change, iterator);
}