#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* value; } ;
typedef  TYPE_3__ svn_sort__item_t ;
struct TYPE_7__ {scalar_t__ sum; } ;
struct TYPE_8__ {TYPE_1__ total; } ;
struct TYPE_10__ {TYPE_2__ node_histogram; } ;
typedef  TYPE_4__ svn_fs_fs__extension_info_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_node_size(const svn_sort__item_t *a,
                  const svn_sort__item_t *b)
{
  const svn_fs_fs__extension_info_t *lhs = a->value;
  const svn_fs_fs__extension_info_t *rhs = b->value;
  apr_int64_t diff = lhs->node_histogram.total.sum
                   - rhs->node_histogram.total.sum;

  return diff > 0 ? -1 : (diff < 0 ? 1 : 0);
}