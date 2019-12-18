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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {char const* parent_relpath; int /*<<< orphan*/  tree_conflict_data; int /*<<< orphan*/  local_relpath; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_1__ db_actual_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 TYPE_1__* MAYBE_ALLOC (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_actual_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_actual_only_entries(apr_hash_t *tree_conflicts,
                          svn_sqlite__db_t *sdb,
                          svn_wc__db_t *db,
                          const char *wri_abspath,
                          apr_int64_t wc_id,
                          const char *parent_relpath,
                          apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(scratch_pool, tree_conflicts);
       hi;
       hi = apr_hash_next(hi))
    {
      db_actual_node_t *actual_node = NULL;

      actual_node = MAYBE_ALLOC(actual_node, scratch_pool);
      actual_node->wc_id = wc_id;
      actual_node->local_relpath = apr_hash_this_key(hi);
      actual_node->parent_relpath = parent_relpath;
      actual_node->tree_conflict_data = apr_hash_this_val(hi);

      SVN_ERR(insert_actual_node(sdb, db, wri_abspath, actual_node,
                                 scratch_pool));
    }

  return SVN_NO_ERROR;
}