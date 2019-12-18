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
struct svnadmin_opt_state {int /*<<< orphan*/  quiet; int /*<<< orphan*/  end_revision; int /*<<< orphan*/  start_revision; int /*<<< orphan*/  repository_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_revnum (scalar_t__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_repos (int /*<<< orphan*/ **,int /*<<< orphan*/ ,struct svnadmin_opt_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_deltify_revision (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
subcommand_deltify(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  struct svnadmin_opt_state *opt_state = baton;
  svn_repos_t *repos;
  svn_fs_t *fs;
  svn_revnum_t start = SVN_INVALID_REVNUM, end = SVN_INVALID_REVNUM;
  svn_revnum_t youngest, revision;
  apr_pool_t *subpool = svn_pool_create(pool);

  /* Expect no more arguments. */
  SVN_ERR(parse_args(NULL, os, 0, 0, pool));

  SVN_ERR(open_repos(&repos, opt_state->repository_path, opt_state, pool));
  fs = svn_repos_fs(repos);
  SVN_ERR(svn_fs_youngest_rev(&youngest, fs, pool));

  /* Find the revision numbers at which to start and end. */
  SVN_ERR(get_revnum(&start, &opt_state->start_revision,
                     youngest, repos, pool));
  SVN_ERR(get_revnum(&end, &opt_state->end_revision,
                     youngest, repos, pool));

  /* Fill in implied revisions if necessary. */
  if (start == SVN_INVALID_REVNUM)
    start = youngest;
  if (end == SVN_INVALID_REVNUM)
    end = start;

  if (start > end)
    return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
       _("First revision cannot be higher than second"));

  /* Loop over the requested revision range, performing the
     predecessor deltification on paths changed in each. */
  for (revision = start; revision <= end; revision++)
    {
      svn_pool_clear(subpool);
      SVN_ERR(check_cancel(NULL));
      if (! opt_state->quiet)
        SVN_ERR(svn_cmdline_printf(subpool, _("Deltifying revision %ld..."),
                                   revision));
      SVN_ERR(svn_fs_deltify_revision(fs, revision, subpool));
      if (! opt_state->quiet)
        SVN_ERR(svn_cmdline_printf(subpool, _("done.\n")));
    }
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}