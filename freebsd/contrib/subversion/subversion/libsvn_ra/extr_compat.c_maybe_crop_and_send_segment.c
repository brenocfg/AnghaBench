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
struct TYPE_5__ {char const* path; scalar_t__ range_start; scalar_t__ range_end; } ;
typedef  TYPE_1__ svn_location_segment_t ;
typedef  int /*<<< orphan*/ * (* svn_location_segment_receiver_t ) (TYPE_1__*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
maybe_crop_and_send_segment(const char *path,
                            svn_revnum_t start_rev,
                            svn_revnum_t range_start,
                            svn_revnum_t range_end,
                            svn_location_segment_receiver_t receiver,
                            void *receiver_baton,
                            apr_pool_t *pool)
{
  svn_location_segment_t *segment = apr_pcalloc(pool, sizeof(*segment));
  segment->path = path ? ((*path == '/') ? path + 1 : path) : NULL;
  segment->range_start = range_start;
  segment->range_end = range_end;
  if (segment->range_start <= start_rev)
    {
      if (segment->range_end > start_rev)
        segment->range_end = start_rev;
      return receiver(segment, receiver_baton, pool);
    }
  return SVN_NO_ERROR;
}