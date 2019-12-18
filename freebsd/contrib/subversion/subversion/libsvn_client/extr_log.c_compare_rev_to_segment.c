#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_2__ {scalar_t__ range_start; scalar_t__ range_end; } ;
typedef  TYPE_1__ svn_location_segment_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_rev_to_segment(const void *key_p,
                       const void *element_p)
{
  svn_revnum_t rev =
    * (svn_revnum_t *)key_p;
  const svn_location_segment_t *segment =
    *((const svn_location_segment_t * const *) element_p);

  if (rev < segment->range_start)
    return -1;
  else if (rev > segment->range_end)
    return 1;
  else
    return 0;
}