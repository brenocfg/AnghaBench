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
struct TYPE_2__ {int /*<<< orphan*/  repository_path; } ;
typedef  TYPE_1__ svnfsfs__opt_state ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__stats_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_cancel ; 
 int /*<<< orphan*/  open_fs (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_progress ; 
 int /*<<< orphan*/  print_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  svn_fs_fs__get_stats (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
subcommand__stats(apr_getopt_t *os, void *baton, apr_pool_t *pool)
{
  svnfsfs__opt_state *opt_state = baton;
  svn_fs_fs__stats_t *stats;
  svn_fs_t *fs;

  printf("Reading revisions\n");
  SVN_ERR(open_fs(&fs, opt_state->repository_path, pool));
  SVN_ERR(svn_fs_fs__get_stats(&stats, fs, print_progress, NULL,
                               check_cancel, NULL, pool, pool));

  print_stats(stats, pool);

  return SVN_NO_ERROR;
}