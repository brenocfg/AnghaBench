#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_4__ {int /*<<< orphan*/  revision_file; int /*<<< orphan*/  revision; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_x__changes_context_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_x__ensure_revision_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__create_changes_context(svn_fs_x__changes_context_t **context,
                                 svn_fs_t *fs,
                                 svn_revnum_t rev,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  svn_fs_x__changes_context_t *result = apr_pcalloc(result_pool,
                                                    sizeof(*result));
  result->fs = fs;
  result->revision = rev;

  SVN_ERR(svn_fs_x__ensure_revision_exists(rev, fs, scratch_pool));
  SVN_ERR(svn_fs_x__rev_file_init(&result->revision_file, fs, rev,
                                  result_pool));

  *context = result;
  return SVN_NO_ERROR;
}