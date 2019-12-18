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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_newline (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_copy(svn_fs_root_t *from_root,
        const char *from_path,
        svn_fs_root_t *to_root,
        const char *to_path,
        apr_pool_t *pool)
{
  SVN_ERR(check_newline(to_path, pool));

  return svn_error_trace(copy_helper(from_root,
                                     svn_fs__canonicalize_abspath(from_path,
                                                                  pool),
                                     to_root,
                                     svn_fs__canonicalize_abspath(to_path,
                                                                  pool),
                                     TRUE, pool));
}