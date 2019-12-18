#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_12__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_location_segment_receiver_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {TYPE_3__* (* get_location_segments ) (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_RA_NOT_IMPLEMENTED ; 
 TYPE_3__* stub1 (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_ra__location_segments_from_log (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_ra_get_location_segments(svn_ra_session_t *session,
                             const char *path,
                             svn_revnum_t peg_revision,
                             svn_revnum_t start_rev,
                             svn_revnum_t end_rev,
                             svn_location_segment_receiver_t receiver,
                             void *receiver_baton,
                             apr_pool_t *pool)
{
  svn_error_t *err;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(path));
  err = session->vtable->get_location_segments(session, path, peg_revision,
                                               start_rev, end_rev,
                                               receiver, receiver_baton, pool);
  if (err && (err->apr_err == SVN_ERR_RA_NOT_IMPLEMENTED))
    {
      svn_error_clear(err);

      /* Do it the slow way, using get-logs, for older servers. */
      err = svn_ra__location_segments_from_log(session, path,
                                               peg_revision, start_rev,
                                               end_rev, receiver,
                                               receiver_baton, pool);
    }
  return err;
}