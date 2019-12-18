#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct merge_dir_baton_t {scalar_t__ pending_deletes; int /*<<< orphan*/  pool; } ;
struct TYPE_5__ {scalar_t__ ancestral; } ;
struct TYPE_6__ {int /*<<< orphan*/  merged_abspaths; scalar_t__ added_abspaths; scalar_t__ reintegrate_merge; TYPE_1__ merge_source; } ;
typedef  TYPE_2__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  notify_merge_begin (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_path (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_node_kind_to_word (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
record_update_delete(merge_cmd_baton_t *merge_b,
                     struct merge_dir_baton_t *parent_db,
                     const char *local_abspath,
                     svn_node_kind_t kind,
                     apr_pool_t *scratch_pool)
{
  /* Update the lists of merged, skipped, tree-conflicted and added paths. */
  if (merge_b->merge_source.ancestral
      || merge_b->reintegrate_merge)
    {
      /* Issue #4166: If a previous merge added NOTIFY_ABSPATH, but we
         are now deleting it, then remove it from the list of added
         paths. */
      svn_hash_sets(merge_b->added_abspaths, local_abspath, NULL);
      store_path(merge_b->merged_abspaths, local_abspath);
    }

  SVN_ERR(notify_merge_begin(merge_b, local_abspath, TRUE, scratch_pool));

  if (parent_db)
    {
      const char *dup_abspath = apr_pstrdup(parent_db->pool, local_abspath);

      if (!parent_db->pending_deletes)
        parent_db->pending_deletes = apr_hash_make(parent_db->pool);

      svn_hash_sets(parent_db->pending_deletes, dup_abspath,
                    svn_node_kind_to_word(kind));
    }

  return SVN_NO_ERROR;
}