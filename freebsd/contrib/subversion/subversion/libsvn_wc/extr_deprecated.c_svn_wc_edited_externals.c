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
struct TYPE_3__ {int /*<<< orphan*/ * externals_new; int /*<<< orphan*/ * externals_old; } ;
typedef  TYPE_1__ svn_wc_traversal_info_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */

void
svn_wc_edited_externals(apr_hash_t **externals_old,
                        apr_hash_t **externals_new,
                        svn_wc_traversal_info_t *traversal_info)
{
  *externals_old = traversal_info->externals_old;
  *externals_new = traversal_info->externals_new;
}