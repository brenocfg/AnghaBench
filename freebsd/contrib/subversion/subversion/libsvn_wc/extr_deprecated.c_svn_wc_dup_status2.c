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
struct TYPE_5__ {scalar_t__ tree_conflict; void* ood_last_cmt_author; void* url; scalar_t__ repos_lock; scalar_t__ entry; } ;
typedef  TYPE_1__ svn_wc_status2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ conflict_description_dup (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_lock_dup (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_entry_dup (scalar_t__,int /*<<< orphan*/ *) ; 

svn_wc_status2_t *
svn_wc_dup_status2(const svn_wc_status2_t *orig_stat,
                   apr_pool_t *pool)
{
  svn_wc_status2_t *new_stat = apr_palloc(pool, sizeof(*new_stat));

  /* Shallow copy all members. */
  *new_stat = *orig_stat;

  /* Now go back and dup the deep items into this pool. */
  if (orig_stat->entry)
    new_stat->entry = svn_wc_entry_dup(orig_stat->entry, pool);

  if (orig_stat->repos_lock)
    new_stat->repos_lock = svn_lock_dup(orig_stat->repos_lock, pool);

  if (orig_stat->url)
    new_stat->url = apr_pstrdup(pool, orig_stat->url);

  if (orig_stat->ood_last_cmt_author)
    new_stat->ood_last_cmt_author
      = apr_pstrdup(pool, orig_stat->ood_last_cmt_author);

  if (orig_stat->tree_conflict)
    new_stat->tree_conflict
      = conflict_description_dup(orig_stat->tree_conflict, pool);

  /* Return the new hotness. */
  return new_stat;
}