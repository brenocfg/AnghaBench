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
struct TYPE_2__ {scalar_t__ range_start; } ;
typedef  TYPE_1__ svn_location_segment_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_segments(const void *a, const void *b)
{
  const svn_location_segment_t *a_seg
    = *((const svn_location_segment_t * const *) a);
  const svn_location_segment_t *b_seg
    = *((const svn_location_segment_t * const *) b);
  if (a_seg->range_start == b_seg->range_start)
    return 0;
  return (a_seg->range_start < b_seg->range_start) ? -1 : 1;
}