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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  repos_root; int /*<<< orphan*/ * repos_locks; } ;
struct edit_baton {TYPE_1__ wb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 

svn_error_t *
svn_wc_status_set_repos_locks(void *edit_baton,
                              apr_hash_t *locks,
                              const char *repos_root,
                              apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;

  eb->wb.repos_locks = locks;
  eb->wb.repos_root = apr_pstrdup(pool, repos_root);

  return SVN_NO_ERROR;
}