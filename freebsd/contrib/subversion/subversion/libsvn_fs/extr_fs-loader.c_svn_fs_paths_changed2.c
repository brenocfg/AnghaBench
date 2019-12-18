#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_2__* vtable; } ;
typedef  TYPE_3__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_iterator_t ;
struct TYPE_15__ {char* data; int /*<<< orphan*/  len; } ;
struct TYPE_18__ {TYPE_1__ path; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; scalar_t__ copyfrom_known; int /*<<< orphan*/  change_kind; } ;
typedef  TYPE_4__ svn_fs_path_change3_t ;
struct TYPE_19__ {int /*<<< orphan*/  text_mod; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; scalar_t__ copyfrom_known; } ;
typedef  TYPE_5__ svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* paths_changed ) (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_EMULATE_PATHS_CHANGED ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__get_deleted_node (TYPE_3__**,char const**,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_id (int /*<<< orphan*/  const**,TYPE_3__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_fs_path_change2_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 
 int /*<<< orphan*/  svn_fs_path_change_get (TYPE_4__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_paths_changed3 (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_paths_changed2(apr_hash_t **changed_paths_p,
                      svn_fs_root_t *root,
                      apr_pool_t *pool)
{
  svn_boolean_t emulate =    !root->vtable->paths_changed
                          || SVN_FS_EMULATE_PATHS_CHANGED;

  if (emulate)
    {
      apr_pool_t *scratch_pool = svn_pool_create(pool);
      apr_hash_t *changes = svn_hash__make(pool);

      svn_fs_path_change_iterator_t *iterator;
      svn_fs_path_change3_t *change;

      SVN_ERR(svn_fs_paths_changed3(&iterator, root, scratch_pool,
                                    scratch_pool));

      SVN_ERR(svn_fs_path_change_get(&change, iterator));
      while (change)
        {
          svn_fs_path_change2_t *copy;
          const svn_fs_id_t *id_copy;
          const char *change_path = change->path.data;
          svn_fs_root_t *change_root = root;

          /* Copy CHANGE to old API struct. */
          if (change->change_kind == svn_fs_path_change_delete)
            SVN_ERR(svn_fs__get_deleted_node(&change_root, &change_path,
                                             change_root, change_path,
                                             scratch_pool, scratch_pool));

          SVN_ERR(svn_fs_node_id(&id_copy, change_root, change_path, pool));

          copy = svn_fs_path_change2_create(id_copy, change->change_kind,
                                            pool);
          copy->copyfrom_known = change->copyfrom_known;
          if (   copy->copyfrom_known
              && SVN_IS_VALID_REVNUM(change->copyfrom_rev))
            {
              copy->copyfrom_rev = change->copyfrom_rev;
              copy->copyfrom_path = apr_pstrdup(pool, change->copyfrom_path);
            }
          copy->mergeinfo_mod = change->mergeinfo_mod;
          copy->node_kind = change->node_kind;
          copy->prop_mod = change->prop_mod;
          copy->text_mod = change->text_mod;

          svn_hash_sets(changes, apr_pstrmemdup(pool, change->path.data,
                                                change->path.len), copy);

          /* Next change. */
          SVN_ERR(svn_fs_path_change_get(&change, iterator));
        }
      svn_pool_destroy(scratch_pool);

      *changed_paths_p = changes;
    }
  else
    {
      SVN_ERR(root->vtable->paths_changed(changed_paths_p, root, pool));
    }

  return SVN_NO_ERROR;
}