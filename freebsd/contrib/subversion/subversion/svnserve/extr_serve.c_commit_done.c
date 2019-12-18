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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  post_commit_err; int /*<<< orphan*/  author; int /*<<< orphan*/  date; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_commit_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/ ** post_commit_err; int /*<<< orphan*/ ** author; int /*<<< orphan*/ ** date; int /*<<< orphan*/ * new_rev; } ;
typedef  TYPE_2__ commit_callback_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *commit_done(const svn_commit_info_t *commit_info,
                                void *baton, apr_pool_t *pool)
{
  commit_callback_baton_t *ccb = baton;

  *ccb->new_rev = commit_info->revision;
  *ccb->date = commit_info->date
    ? apr_pstrdup(ccb->pool, commit_info->date): NULL;
  *ccb->author = commit_info->author
    ? apr_pstrdup(ccb->pool, commit_info->author) : NULL;
  *ccb->post_commit_err = commit_info->post_commit_err
    ? apr_pstrdup(ccb->pool, commit_info->post_commit_err) : NULL;
  return SVN_NO_ERROR;
}