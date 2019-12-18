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
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_5__ {scalar_t__ range_start; scalar_t__ range_end; } ;
typedef  TYPE_1__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  (* svn_location_segment_receiver_t ) (TYPE_1__*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
maybe_crop_and_send_segment(svn_location_segment_t *segment,
                            svn_revnum_t start_rev,
                            svn_revnum_t end_rev,
                            svn_location_segment_receiver_t receiver,
                            void *receiver_baton,
                            apr_pool_t *pool)
{
  /* We only want to transmit this segment if some portion of it
     is between our END_REV and START_REV. */
  if (! ((segment->range_start > start_rev)
         || (segment->range_end < end_rev)))
    {
      /* Correct our segment range when the range straddles one of
         our requested revision boundaries. */
      if (segment->range_start < end_rev)
        segment->range_start = end_rev;
      if (segment->range_end > start_rev)
        segment->range_end = start_rev;
      SVN_ERR(receiver(segment, receiver_baton, pool));
    }
  return SVN_NO_ERROR;
}