#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ node_status; int prop_status; scalar_t__ repos_node_status; int text_status; scalar_t__ repos_text_status; scalar_t__ kind; scalar_t__ conflicted; scalar_t__ versioned; int /*<<< orphan*/  repos_prop_status; int /*<<< orphan*/  switched; int /*<<< orphan*/  ood_changed_author; int /*<<< orphan*/  ood_kind; int /*<<< orphan*/  ood_changed_date; int /*<<< orphan*/  ood_changed_rev; scalar_t__ repos_relpath; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  repos_lock; int /*<<< orphan*/  copied; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
struct TYPE_18__ {scalar_t__ text_status; int prop_status; scalar_t__ repos_text_status; int pristine_text_status; int pristine_prop_status; int /*<<< orphan*/  repos_prop_status; int /*<<< orphan*/  switched; int /*<<< orphan*/  tree_conflict; int /*<<< orphan*/  ood_last_cmt_author; int /*<<< orphan*/  ood_kind; int /*<<< orphan*/  ood_last_cmt_date; int /*<<< orphan*/  ood_last_cmt_rev; int /*<<< orphan*/  url; int /*<<< orphan*/  repos_lock; int /*<<< orphan*/  copied; int /*<<< orphan*/  const* entry; } ;
typedef  TYPE_2__ svn_wc_status2_t ;
typedef  int /*<<< orphan*/  svn_wc_entry_t ;
struct TYPE_19__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_description2_t ;
struct TYPE_20__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 scalar_t__ SVN_ERR_NODE_UNEXPECTED_KIND ; 
 TYPE_4__* SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_lock_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__cd2_to_cd (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__get_entry (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__get_tree_conflict (int /*<<< orphan*/  const**,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__internal_conflicted_p (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_status_added ; 
#define  svn_wc_status_conflicted 131 
 scalar_t__ svn_wc_status_deleted ; 
 scalar_t__ svn_wc_status_missing ; 
#define  svn_wc_status_modified 130 
#define  svn_wc_status_none 129 
#define  svn_wc_status_normal 128 
 scalar_t__ svn_wc_status_obstructed ; 
 scalar_t__ svn_wc_status_replaced ; 

svn_error_t *
svn_wc__status2_from_3(svn_wc_status2_t **status,
                       const svn_wc_status3_t *old_status,
                       svn_wc_context_t *wc_ctx,
                       const char *local_abspath,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  const svn_wc_entry_t *entry = NULL;

  if (old_status == NULL)
    {
      *status = NULL;
      return SVN_NO_ERROR;
    }

  *status = apr_pcalloc(result_pool, sizeof(**status));

  if (old_status->versioned)
    {
      svn_error_t *err;
      err= svn_wc__get_entry(&entry, wc_ctx->db, local_abspath, FALSE,
                             svn_node_unknown, result_pool, scratch_pool);

      if (err && err->apr_err == SVN_ERR_NODE_UNEXPECTED_KIND)
        svn_error_clear(err);
      else
        SVN_ERR(err);
    }

  (*status)->entry = entry;
  (*status)->copied = old_status->copied;
  (*status)->repos_lock = svn_lock_dup(old_status->repos_lock, result_pool);

  if (old_status->repos_relpath)
    (*status)->url = svn_path_url_add_component2(old_status->repos_root_url,
                                                 old_status->repos_relpath,
                                                 result_pool);
  (*status)->ood_last_cmt_rev = old_status->ood_changed_rev;
  (*status)->ood_last_cmt_date = old_status->ood_changed_date;
  (*status)->ood_kind = old_status->ood_kind;
  (*status)->ood_last_cmt_author = old_status->ood_changed_author;

  if (old_status->conflicted)
    {
      const svn_wc_conflict_description2_t *tree_conflict2;
      SVN_ERR(svn_wc__get_tree_conflict(&tree_conflict2, wc_ctx, local_abspath,
                                        scratch_pool, scratch_pool));
      (*status)->tree_conflict = svn_wc__cd2_to_cd(tree_conflict2, result_pool);
    }

  (*status)->switched = old_status->switched;

  (*status)->text_status = old_status->node_status;
  (*status)->prop_status = old_status->prop_status;

  (*status)->repos_text_status = old_status->repos_node_status;
  (*status)->repos_prop_status = old_status->repos_prop_status;

  /* Some values might be inherited from properties */
  if (old_status->node_status == svn_wc_status_modified
      || old_status->node_status == svn_wc_status_conflicted)
    (*status)->text_status = old_status->text_status;

  /* (Currently a no-op, but just make sure it is ok) */
  if (old_status->repos_node_status == svn_wc_status_modified
      || old_status->repos_node_status == svn_wc_status_conflicted)
    (*status)->repos_text_status = old_status->repos_text_status;

  if (old_status->node_status == svn_wc_status_added)
    (*status)->prop_status = svn_wc_status_none; /* No separate info */

  /* Find pristine_text_status value */
  switch (old_status->text_status)
    {
      case svn_wc_status_none:
      case svn_wc_status_normal:
      case svn_wc_status_modified:
        (*status)->pristine_text_status = old_status->text_status;
        break;
      case svn_wc_status_conflicted:
      default:
        /* ### Fetch compare data, or fall back to the documented
               not retrieved behavior? */
        (*status)->pristine_text_status = svn_wc_status_none;
        break;
    }

  /* Find pristine_prop_status value */
  switch (old_status->prop_status)
    {
      case svn_wc_status_none:
      case svn_wc_status_normal:
      case svn_wc_status_modified:
        if (old_status->node_status != svn_wc_status_added
            && old_status->node_status != svn_wc_status_deleted
            && old_status->node_status != svn_wc_status_replaced)
          {
            (*status)->pristine_prop_status = old_status->prop_status;
          }
        else
          (*status)->pristine_prop_status = svn_wc_status_none;
        break;
      case svn_wc_status_conflicted:
      default:
        /* ### Fetch compare data, or fall back to the documented
               not retrieved behavior? */
        (*status)->pristine_prop_status = svn_wc_status_none;
        break;
    }

  if (old_status->versioned
      && old_status->conflicted
      && old_status->node_status != svn_wc_status_obstructed
      && (old_status->kind == svn_node_file
          || old_status->node_status != svn_wc_status_missing))
    {
      svn_boolean_t text_conflict_p, prop_conflict_p;

      /* The entry says there was a conflict, but the user might have
         marked it as resolved by deleting the artifact files, so check
         for that. */
      SVN_ERR(svn_wc__internal_conflicted_p(&text_conflict_p,
                                            &prop_conflict_p,
                                            NULL,
                                            wc_ctx->db, local_abspath,
                                            scratch_pool));

      if (text_conflict_p)
        (*status)->text_status = svn_wc_status_conflicted;

      if (prop_conflict_p)
        (*status)->prop_status = svn_wc_status_conflicted;
    }

  return SVN_NO_ERROR;
}