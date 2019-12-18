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
struct TYPE_4__ {int /*<<< orphan*/  lock_tokens; int /*<<< orphan*/  username; } ;
typedef  TYPE_1__ svn_fs_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 

svn_error_t *
svn_fs_create_access(svn_fs_access_t **access_ctx,
                     const char *username,
                     apr_pool_t *pool)
{
  svn_fs_access_t *ac;

  SVN_ERR_ASSERT(username != NULL);

  ac = apr_pcalloc(pool, sizeof(*ac));
  ac->username = apr_pstrdup(pool, username);
  ac->lock_tokens = apr_hash_make(pool);
  *access_ctx = ac;

  return SVN_NO_ERROR;
}