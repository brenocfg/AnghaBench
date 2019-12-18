#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* value; } ;
typedef  TYPE_2__ svn_sort__item_t ;
struct TYPE_8__ {TYPE_1__* dirent; } ;
typedef  TYPE_3__ svn_client_shelved_patch_info_t ;
struct TYPE_6__ {scalar_t__ mtime; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_shelved_patch_infos_by_mtime(const svn_sort__item_t *a,
                                     const svn_sort__item_t *b)
{
  svn_client_shelved_patch_info_t *a_val = a->value;
  svn_client_shelved_patch_info_t *b_val = b->value;

  return (a_val->dirent->mtime < b_val->dirent->mtime)
           ? -1 : (a_val->dirent->mtime > b_val->dirent->mtime) ? 1 : 0;
}