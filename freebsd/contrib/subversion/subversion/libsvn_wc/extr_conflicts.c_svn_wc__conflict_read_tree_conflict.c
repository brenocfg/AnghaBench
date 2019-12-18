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
typedef  int svn_wc_conflict_reason_t ;
typedef  int svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; struct TYPE_5__* next; struct TYPE_5__* children; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_MISSING ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_TOKEN_UNKNOWN ; 
 int /*<<< orphan*/  SVN_WC__CONFLICT_KIND_TREE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  action_map ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conflict__get_conflict (TYPE_1__**,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reason_map ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int svn_token__from_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_wc_conflict_action_edit ; 
 int svn_wc_conflict_reason_edited ; 
 int svn_wc_conflict_reason_moved_away ; 

svn_error_t *
svn_wc__conflict_read_tree_conflict(svn_wc_conflict_reason_t *reason,
                                    svn_wc_conflict_action_t *action,
                                    const char **move_src_op_root_abspath,
                                    svn_wc__db_t *db,
                                    const char *wri_abspath,
                                    const svn_skel_t *conflict_skel,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  svn_skel_t *tree_conflict;
  const svn_skel_t *c;
  svn_boolean_t is_moved_away = FALSE;

  SVN_ERR(conflict__get_conflict(&tree_conflict, conflict_skel,
                                 SVN_WC__CONFLICT_KIND_TREE));

  if (!tree_conflict)
    return svn_error_create(SVN_ERR_WC_MISSING, NULL, _("Conflict not set"));

  c = tree_conflict->children;

  c = c->next; /* Skip "tree" */

  c = c->next; /* Skip markers */

  {
    int value = svn_token__from_mem(reason_map, c->data, c->len);

    if (reason)
      {
        if (value != SVN_TOKEN_UNKNOWN)
          *reason = value;
        else
          *reason = svn_wc_conflict_reason_edited;
      }

      is_moved_away = (value == svn_wc_conflict_reason_moved_away);
    }
  c = c->next;

  if (action)
    {
      int value = svn_token__from_mem(action_map, c->data, c->len);

      if (value != SVN_TOKEN_UNKNOWN)
        *action = value;
      else
        *action = svn_wc_conflict_action_edit;
    }

  c = c->next;

  if (move_src_op_root_abspath)
    {
      /* Only set for update and switch tree conflicts */
      if (c && is_moved_away)
        {
          const char *move_src_op_root_relpath
                            = apr_pstrmemdup(scratch_pool, c->data, c->len);

          SVN_ERR(svn_wc__db_from_relpath(move_src_op_root_abspath,
                                          db, wri_abspath,
                                          move_src_op_root_relpath,
                                          result_pool, scratch_pool));
        }
      else
        *move_src_op_root_abspath = NULL;
    }

  return SVN_NO_ERROR;
}