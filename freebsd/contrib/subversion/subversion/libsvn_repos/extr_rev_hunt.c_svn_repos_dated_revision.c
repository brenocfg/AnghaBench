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
typedef  int svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_time (scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_refresh_revision_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_dated_revision(svn_revnum_t *revision,
                         svn_repos_t *repos,
                         apr_time_t tm,
                         apr_pool_t *pool)
{
  svn_revnum_t rev_mid, rev_top, rev_bot, rev_latest;
  apr_time_t this_time;
  svn_fs_t *fs = repos->fs;

  /* Initialize top and bottom values of binary search. */
  SVN_ERR(svn_fs_youngest_rev(&rev_latest, fs, pool));
  SVN_ERR(svn_fs_refresh_revision_props(fs, pool));
  rev_bot = 0;
  rev_top = rev_latest;

  while (rev_bot <= rev_top)
    {
      rev_mid = (rev_top + rev_bot) / 2;
      SVN_ERR(get_time(&this_time, fs, rev_mid, pool));

      if (this_time > tm)/* we've overshot */
        {
          apr_time_t previous_time;

          if ((rev_mid - 1) < 0)
            {
              *revision = 0;
              break;
            }

          /* see if time falls between rev_mid and rev_mid-1: */
          SVN_ERR(get_time(&previous_time, fs, rev_mid - 1, pool));
          if (previous_time <= tm)
            {
              *revision = rev_mid - 1;
              break;
            }

          rev_top = rev_mid - 1;
        }

      else if (this_time < tm) /* we've undershot */
        {
          apr_time_t next_time;

          if ((rev_mid + 1) > rev_latest)
            {
              *revision = rev_latest;
              break;
            }

          /* see if time falls between rev_mid and rev_mid+1: */
          SVN_ERR(get_time(&next_time, fs, rev_mid + 1, pool));
          if (next_time > tm)
            {
              *revision = rev_mid;
              break;
            }

          rev_bot = rev_mid + 1;
        }

      else
        {
          *revision = rev_mid;  /* exact match! */
          break;
        }
    }

  return SVN_NO_ERROR;
}