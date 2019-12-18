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
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ compare_p2l_info ; 
 int /*<<< orphan*/  svn_sort__array (int /*<<< orphan*/ *,int (*) (void const*,void const*)) ; 

__attribute__((used)) static void
sort_items(apr_array_header_t *entries)
{
  svn_sort__array(entries,
                  (int (*)(const void *, const void *))compare_p2l_info);
}