#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sum; int /*<<< orphan*/  count; } ;
struct TYPE_7__ {TYPE_2__* lines; TYPE_1__ total; } ;
typedef  TYPE_3__ svn_fs_fs__histogram_t ;
typedef  size_t apr_size_t ;
typedef  int apr_int64_t ;
struct TYPE_6__ {int sum; int /*<<< orphan*/  count; } ;

/* Variables and functions */

__attribute__((used)) static void
add_to_histogram(svn_fs_fs__histogram_t *histogram,
                 apr_int64_t size)
{
  apr_int64_t shift = 0;

  while (((apr_int64_t)(1) << shift) <= size)
    shift++;

  histogram->total.count++;
  histogram->total.sum += size;
  histogram->lines[(apr_size_t)shift].count++;
  histogram->lines[(apr_size_t)shift].sum += size;
}