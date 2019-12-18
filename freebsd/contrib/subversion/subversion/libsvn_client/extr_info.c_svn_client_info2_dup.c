#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ wc_info; scalar_t__ lock; void* last_changed_author; void* repos_UUID; void* repos_root_URL; void* URL; } ;
typedef  TYPE_1__ svn_client_info2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ svn_lock_dup (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_info_dup (scalar_t__,int /*<<< orphan*/ *) ; 

svn_client_info2_t *
svn_client_info2_dup(const svn_client_info2_t *info,
                     apr_pool_t *pool)
{
  svn_client_info2_t *new_info = apr_pmemdup(pool, info, sizeof(*new_info));

  if (new_info->URL)
    new_info->URL = apr_pstrdup(pool, info->URL);
  if (new_info->repos_root_URL)
    new_info->repos_root_URL = apr_pstrdup(pool, info->repos_root_URL);
  if (new_info->repos_UUID)
    new_info->repos_UUID = apr_pstrdup(pool, info->repos_UUID);
  if (info->last_changed_author)
    new_info->last_changed_author = apr_pstrdup(pool, info->last_changed_author);
  if (new_info->lock)
    new_info->lock = svn_lock_dup(info->lock, pool);
  if (new_info->wc_info)
    new_info->wc_info = svn_wc_info_dup(info->wc_info, pool);
  return new_info;
}