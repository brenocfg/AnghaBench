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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/ * rev_file_pool; int /*<<< orphan*/  revision; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_fs__changes_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_error_t *
svn_fs_fs__create_changes_context(svn_fs_fs__changes_context_t **context,
                                  svn_fs_t *fs,
                                  svn_revnum_t rev,
                                  apr_pool_t *result_pool)
{
  svn_fs_fs__changes_context_t *result = apr_pcalloc(result_pool,
                                                     sizeof(*result));
  result->fs = fs;
  result->revision = rev;
  result->rev_file_pool = result_pool;

  *context = result;
  return SVN_NO_ERROR;
}