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
typedef  int /*<<< orphan*/  svn_fs_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs_access_add_lock_token2 (int /*<<< orphan*/ *,char const*,char const*) ; 

svn_error_t *
svn_fs_access_add_lock_token(svn_fs_access_t *access_ctx,
                             const char *token)
{
  return svn_fs_access_add_lock_token2(access_ctx, (const char *) 1, token);
}