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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  svn_fs_x__invalidate_revprop_generation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__revision_prop (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
verify_revprops(svn_fs_t *fs,
                svn_revnum_t start,
                svn_revnum_t end,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *scratch_pool)
{
  svn_revnum_t revision;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  /* Invalidate the revprop generation once.
   * Use the cache inside the loop to speed up packed revprop access. */
  svn_fs_x__invalidate_revprop_generation(fs);

  for (revision = start; revision < end; ++revision)
    {
      svn_string_t *date;
      apr_time_t timetemp;

      svn_pool_clear(iterpool);

      /* Access the svn:date revprop.
       * This implies parsing all revprops for that revision. */
      SVN_ERR(svn_fs_x__revision_prop(&date, fs, revision,
                                      SVN_PROP_REVISION_DATE, FALSE,
                                      iterpool, iterpool));

      /* The time stamp is the only revprop that, if given, needs to
       * have a valid content. */
      if (date)
        SVN_ERR(svn_time_from_cstring(&timetemp, date->data, iterpool));

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}