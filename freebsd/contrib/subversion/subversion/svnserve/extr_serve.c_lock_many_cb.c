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
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct lock_result_t {int /*<<< orphan*/  err; int /*<<< orphan*/  const* lock; } ;
struct lock_many_baton_t {int /*<<< orphan*/  pool; int /*<<< orphan*/  results; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct lock_result_t* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_error_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_result_t*) ; 

__attribute__((used)) static svn_error_t *
lock_many_cb(void *baton,
             const char *path,
             const svn_lock_t *fs_lock,
             svn_error_t *fs_err,
             apr_pool_t *pool)
{
  struct lock_many_baton_t *b = baton;
  struct lock_result_t *result = apr_palloc(b->pool,
                                            sizeof(struct lock_result_t));

  result->lock = fs_lock;
  result->err = svn_error_dup(fs_err);
  svn_hash_sets(b->results, apr_pstrdup(b->pool, path), result);

  return SVN_NO_ERROR;
}