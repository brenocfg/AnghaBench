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
typedef  int /*<<< orphan*/  svn_wc_status3_t ;
struct TYPE_5__ {void* moved_to_abspath; void* moved_from_abspath; int /*<<< orphan*/ * backwards_compatibility_baton; void* repos_lock; void* ood_changed_author; void* changelist; void* lock; void* changed_author; void* repos_relpath; void* repos_uuid; void* repos_root_url; void* local_abspath; } ;
typedef  TYPE_1__ svn_client_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 
 void* svn_lock_dup (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_dup_status3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_client_status_t *
svn_client_status_dup(const svn_client_status_t *status,
                      apr_pool_t *result_pool)
{
  svn_client_status_t *st = apr_palloc(result_pool, sizeof(*st));

  *st = *status;

  if (status->local_abspath)
    st->local_abspath = apr_pstrdup(result_pool, status->local_abspath);

  if (status->repos_root_url)
    st->repos_root_url = apr_pstrdup(result_pool, status->repos_root_url);

  if (status->repos_uuid)
    st->repos_uuid = apr_pstrdup(result_pool, status->repos_uuid);

  if (status->repos_relpath)
    st->repos_relpath = apr_pstrdup(result_pool, status->repos_relpath);

  if (status->changed_author)
    st->changed_author = apr_pstrdup(result_pool, status->changed_author);

  if (status->lock)
    st->lock = svn_lock_dup(status->lock, result_pool);

  if (status->changelist)
    st->changelist = apr_pstrdup(result_pool, status->changelist);

  if (status->ood_changed_author)
    st->ood_changed_author = apr_pstrdup(result_pool, status->ood_changed_author);

  if (status->repos_lock)
    st->repos_lock = svn_lock_dup(status->repos_lock, result_pool);

  if (status->backwards_compatibility_baton)
    {
      const svn_wc_status3_t *wc_st = status->backwards_compatibility_baton;

      st->backwards_compatibility_baton = svn_wc_dup_status3(wc_st,
                                                             result_pool);
    }

  if (status->moved_from_abspath)
    st->moved_from_abspath =
      apr_pstrdup(result_pool, status->moved_from_abspath);

  if (status->moved_to_abspath)
    st->moved_to_abspath = apr_pstrdup(result_pool, status->moved_to_abspath);

  return st;
}