#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work_item_baton_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; struct TYPE_10__* next; TYPE_1__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_9__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_prop_conflict (TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__conflict_skel_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_update (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_mark_conflict (int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
run_set_property_conflict_marker(work_item_baton_t *wqb,
                                 svn_wc__db_t *db,
                                 const svn_skel_t *work_item,
                                 const char *wri_abspath,
                                 svn_cancel_func_t cancel_func,
                                 void *cancel_baton,
                                 apr_pool_t *scratch_pool)
{
  const svn_skel_t *arg = work_item->children->next;
  const char *local_relpath;
  const char *local_abspath;
  const char *prej_abspath = NULL;

  local_relpath = apr_pstrmemdup(scratch_pool, arg->data, arg->len);

  SVN_ERR(svn_wc__db_from_relpath(&local_abspath, db, wri_abspath,
                                  local_relpath, scratch_pool, scratch_pool));


  arg = arg->next;
  local_relpath = arg->len ? apr_pstrmemdup(scratch_pool, arg->data, arg->len)
                           : NULL;

  if (local_relpath)
    SVN_ERR(svn_wc__db_from_relpath(&prej_abspath, db, wri_abspath,
                                    local_relpath,
                                    scratch_pool, scratch_pool));

  {
    /* Check if we should combine with a text conflict... */
    svn_skel_t *conflicts;
    apr_hash_t *prop_names;

    SVN_ERR(svn_wc__db_read_conflict(&conflicts, NULL, NULL,
                                     db, local_abspath,
                                     scratch_pool, scratch_pool));

    if (! conflicts)
      {
        /* No conflict exists, create a basic skel */
        conflicts = svn_wc__conflict_skel_create(scratch_pool);

        SVN_ERR(svn_wc__conflict_skel_set_op_update(conflicts, NULL, NULL,
                                                    scratch_pool,
                                                    scratch_pool));
      }

    prop_names = apr_hash_make(scratch_pool);
    SVN_ERR(svn_wc__conflict_skel_add_prop_conflict(conflicts, db,
                                                    local_abspath,
                                                    prej_abspath,
                                                    NULL, NULL, NULL,
                                                    prop_names,
                                                    scratch_pool,
                                                    scratch_pool));

    SVN_ERR(svn_wc__db_op_mark_conflict(db, local_abspath, conflicts,
                                        NULL, scratch_pool));
  }
  return SVN_NO_ERROR;
}