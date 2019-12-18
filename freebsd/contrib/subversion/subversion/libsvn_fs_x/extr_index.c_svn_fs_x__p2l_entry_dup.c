#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int item_count; struct TYPE_5__ const* items; } ;
typedef  TYPE_1__ svn_fs_x__p2l_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 

svn_fs_x__p2l_entry_t *
svn_fs_x__p2l_entry_dup(const svn_fs_x__p2l_entry_t *entry,
                        apr_pool_t *result_pool)
{
  svn_fs_x__p2l_entry_t *new_entry = apr_pmemdup(result_pool, entry,
                                                 sizeof(*new_entry));
  if (new_entry->item_count)
    new_entry->items = apr_pmemdup(result_pool,
                                   entry->items,
                                   entry->item_count * sizeof(*entry->items));

  return new_entry;
}