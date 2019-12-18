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
struct fs_freeze_baton_t {int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  fs_freeze_body ; 
 int /*<<< orphan*/  svn_fs_fs__with_write_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_freeze_body2(void *baton,
                apr_pool_t *pool)
{
  struct fs_freeze_baton_t *b = baton;
  SVN_ERR(svn_fs_fs__with_write_lock(b->fs, fs_freeze_body, baton, pool));

  return SVN_NO_ERROR;
}