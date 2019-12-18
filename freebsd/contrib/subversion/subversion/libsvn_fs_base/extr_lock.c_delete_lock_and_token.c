#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__lock_delete (int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_bdb__lock_token_delete (int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
delete_lock_and_token(const char *lock_token,
                      const char *path,
                      trail_t *trail)
{
  SVN_ERR(svn_fs_bdb__lock_delete(trail->fs, lock_token,
                                  trail, trail->pool));
  return svn_fs_bdb__lock_token_delete(trail->fs, path,
                                       trail, trail->pool);
}