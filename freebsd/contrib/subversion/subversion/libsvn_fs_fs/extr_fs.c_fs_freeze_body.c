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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct fs_freeze_baton_t {int /*<<< orphan*/  freeze_baton; int /*<<< orphan*/  (* freeze_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__exists_rep_cache (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__with_rep_cache_lock (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_freeze_body(void *baton,
               apr_pool_t *pool)
{
  struct fs_freeze_baton_t *b = baton;
  svn_boolean_t exists;

  SVN_ERR(svn_fs_fs__exists_rep_cache(&exists, b->fs, pool));
  if (exists)
    SVN_ERR(svn_fs_fs__with_rep_cache_lock(b->fs,
                                           b->freeze_func, b->freeze_baton,
                                           pool));
  else
    SVN_ERR(b->freeze_func(b->freeze_baton, pool));

  return SVN_NO_ERROR;
}