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
struct TYPE_6__ {int sum; int count; } ;
struct TYPE_7__ {TYPE_2__ total; TYPE_1__* lines; } ;
typedef  TYPE_3__ svn_fs_fs__histogram_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int count; int sum; } ;

/* Variables and functions */
 char* _ (char*) ; 
 char* print_two_power (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,int,char*,int) ; 
 char* svn__ui64toa_sep (int,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_histogram(svn_fs_fs__histogram_t *histogram,
                apr_pool_t *pool)
{
  int first = 0;
  int last = 63;
  int i;

  /* identify non-zero range */
  while (last > 0 && histogram->lines[last].count == 0)
    --last;

  while (first <= last && histogram->lines[first].count == 0)
    ++first;

  /* display histogram lines */
  for (i = last; i >= first; --i)
    printf(_("  %4s .. < %-4s %19s (%2d%%) bytes in %12s (%2d%%) items\n"),
           print_two_power(i-1, pool), print_two_power(i, pool),
           svn__ui64toa_sep(histogram->lines[i].sum, ',', pool),
           (int)(histogram->lines[i].sum * 100 / histogram->total.sum),
           svn__ui64toa_sep(histogram->lines[i].count, ',', pool),
           (int)(histogram->lines[i].count * 100 / histogram->total.count));
}