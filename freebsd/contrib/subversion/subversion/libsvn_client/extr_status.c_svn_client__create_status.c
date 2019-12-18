#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  moved_to_abspath; int /*<<< orphan*/  moved_from_abspath; scalar_t__ conflicted; scalar_t__ versioned; int /*<<< orphan*/  ood_changed_author; int /*<<< orphan*/  ood_changed_date; int /*<<< orphan*/  ood_changed_rev; int /*<<< orphan*/  repos_lock; int /*<<< orphan*/  repos_prop_status; int /*<<< orphan*/  repos_text_status; int /*<<< orphan*/  repos_node_status; int /*<<< orphan*/  ood_kind; int /*<<< orphan*/  depth; int /*<<< orphan*/  changelist; int /*<<< orphan*/  lock; scalar_t__ file_external; int /*<<< orphan*/  switched; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  revision; int /*<<< orphan*/  copied; int /*<<< orphan*/  locked; void* prop_status; void* text_status; void* node_status; int /*<<< orphan*/  filesize; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ kind; char const* local_abspath; int /*<<< orphan*/  moved_to_abspath; int /*<<< orphan*/  moved_from_abspath; void* node_status; void* prop_status; void* text_status; TYPE_1__ const* backwards_compatibility_baton; int /*<<< orphan*/  ood_changed_author; int /*<<< orphan*/  ood_changed_date; int /*<<< orphan*/  ood_changed_rev; int /*<<< orphan*/  repos_lock; int /*<<< orphan*/  repos_prop_status; int /*<<< orphan*/  repos_text_status; int /*<<< orphan*/  repos_node_status; int /*<<< orphan*/  ood_kind; int /*<<< orphan*/  depth; int /*<<< orphan*/  changelist; int /*<<< orphan*/  lock; int /*<<< orphan*/  switched; scalar_t__ file_external; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  revision; int /*<<< orphan*/  copied; int /*<<< orphan*/  wc_is_locked; scalar_t__ conflicted; scalar_t__ versioned; int /*<<< orphan*/  filesize; } ;
typedef  TYPE_2__ svn_client_status_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc_conflicted_p3 (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 void* svn_wc_status_conflicted ; 

svn_error_t *
svn_client__create_status(svn_client_status_t **cst,
                          svn_wc_context_t *wc_ctx,
                          const char *local_abspath,
                          const svn_wc_status3_t *status,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  *cst = apr_pcalloc(result_pool, sizeof(**cst));

  (*cst)->kind = status->kind;
  (*cst)->local_abspath = local_abspath;
  (*cst)->filesize = status->filesize;
  (*cst)->versioned = status->versioned;

  (*cst)->conflicted = status->conflicted;

  (*cst)->node_status = status->node_status;
  (*cst)->text_status = status->text_status;
  (*cst)->prop_status = status->prop_status;

  if (status->kind == svn_node_dir)
    (*cst)->wc_is_locked = status->locked;

  (*cst)->copied = status->copied;
  (*cst)->revision = status->revision;

  (*cst)->changed_rev = status->changed_rev;
  (*cst)->changed_date = status->changed_date;
  (*cst)->changed_author = status->changed_author;

  (*cst)->repos_root_url = status->repos_root_url;
  (*cst)->repos_uuid = status->repos_uuid;
  (*cst)->repos_relpath = status->repos_relpath;

  (*cst)->switched = status->switched;

  (*cst)->file_external = status->file_external;
  if (status->file_external)
    {
      (*cst)->switched = FALSE;
    }

  (*cst)->lock = status->lock;

  (*cst)->changelist = status->changelist;
  (*cst)->depth = status->depth;

  /* Out of date information */
  (*cst)->ood_kind = status->ood_kind;
  (*cst)->repos_node_status = status->repos_node_status;
  (*cst)->repos_text_status = status->repos_text_status;
  (*cst)->repos_prop_status = status->repos_prop_status;
  (*cst)->repos_lock = status->repos_lock;

  (*cst)->ood_changed_rev = status->ood_changed_rev;
  (*cst)->ood_changed_date = status->ood_changed_date;
  (*cst)->ood_changed_author = status->ood_changed_author;

  /* When changing the value of backwards_compatibility_baton, also
     change its use in status4_wrapper_func in deprecated.c */
  (*cst)->backwards_compatibility_baton = status;

  if (status->versioned && status->conflicted)
    {
      svn_boolean_t text_conflicted, prop_conflicted, tree_conflicted;

      /* Note: This checks the on disk markers to automatically hide
               text/property conflicts that are hidden by removing their
               markers */
      SVN_ERR(svn_wc_conflicted_p3(&text_conflicted, &prop_conflicted,
                                   &tree_conflicted, wc_ctx, local_abspath,
                                   scratch_pool));

      if (text_conflicted)
        (*cst)->text_status = svn_wc_status_conflicted;

      if (prop_conflicted)
        (*cst)->prop_status = svn_wc_status_conflicted;

      /* ### Also set this for tree_conflicts? */
      if (text_conflicted || prop_conflicted)
        (*cst)->node_status = svn_wc_status_conflicted;
    }

  (*cst)->moved_from_abspath = status->moved_from_abspath;
  (*cst)->moved_to_abspath = status->moved_to_abspath;

  return SVN_NO_ERROR;
}