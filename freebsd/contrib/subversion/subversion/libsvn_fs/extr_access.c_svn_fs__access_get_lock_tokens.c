#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lock_tokens; } ;
typedef  TYPE_1__ svn_fs_access_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */

apr_hash_t *
svn_fs__access_get_lock_tokens(svn_fs_access_t *access_ctx)
{
  return access_ctx->lock_tokens;
}