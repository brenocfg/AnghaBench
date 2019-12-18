#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  range_end; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  pool; scalar_t__ path; scalar_t__ is_first; } ;
typedef  TYPE_2__ copyfrom_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
copyfrom_info_receiver(svn_location_segment_t *segment,
                       void *baton,
                       apr_pool_t *pool)
{
  copyfrom_info_t *copyfrom_info = baton;

  /* If we've already identified the copy source, there's nothing more
     to do.
     ### FIXME:  We *should* be able to send */
  if (copyfrom_info->path)
    return SVN_NO_ERROR;

  /* If this is the first segment, it's not of interest to us. Otherwise
     (so long as this segment doesn't represent a history gap), it holds
     our path's previous location (from which it was last copied). */
  if (copyfrom_info->is_first)
    {
      copyfrom_info->is_first = FALSE;
    }
  else if (segment->path)
    {
      /* The end of the second non-gap segment is the location copied from.  */
      copyfrom_info->path = apr_pstrdup(copyfrom_info->pool, segment->path);
      copyfrom_info->rev = segment->range_end;

      /* ### FIXME: We *should* be able to return SVN_ERR_CEASE_INVOCATION
         ### here so we don't get called anymore. */
    }

  return SVN_NO_ERROR;
}