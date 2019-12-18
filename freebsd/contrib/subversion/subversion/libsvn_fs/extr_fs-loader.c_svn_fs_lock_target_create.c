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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_4__ {char const* token; int /*<<< orphan*/  current_rev; } ;
typedef  TYPE_1__ svn_fs_lock_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_fs_lock_target_t *
svn_fs_lock_target_create(const char *token,
                          svn_revnum_t current_rev,
                          apr_pool_t *result_pool)
{
  svn_fs_lock_target_t *target = apr_palloc(result_pool, sizeof(*target));

  target->token = token;
  target->current_rev = current_rev;

  return target;
}