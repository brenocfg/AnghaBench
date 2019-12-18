#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnadmin_opt_state {int /*<<< orphan*/  end_revision; int /*<<< orphan*/  start_revision; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_revnum (scalar_t__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_dump_range(svn_revnum_t *lower,
               svn_revnum_t *upper,
               svn_repos_t *repos,
               struct svnadmin_opt_state *opt_state,
               apr_pool_t *scratch_pool)
{
  svn_fs_t *fs;
  svn_revnum_t youngest;

  *lower = SVN_INVALID_REVNUM;
  *upper = SVN_INVALID_REVNUM;

  fs = svn_repos_fs(repos);
  SVN_ERR(svn_fs_youngest_rev(&youngest, fs, scratch_pool));

  /* Find the revision numbers at which to start and end. */
  SVN_ERR(get_revnum(lower, &opt_state->start_revision,
                     youngest, repos, scratch_pool));
  SVN_ERR(get_revnum(upper, &opt_state->end_revision,
                     youngest, repos, scratch_pool));

  /* Fill in implied revisions if necessary. */
  if (*lower == SVN_INVALID_REVNUM)
    {
      *lower = 0;
      *upper = youngest;
    }
  else if (*upper == SVN_INVALID_REVNUM)
    {
      *upper = *lower;
    }

  if (*lower > *upper)
    return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
       _("First revision cannot be higher than second"));

  return SVN_NO_ERROR;
}