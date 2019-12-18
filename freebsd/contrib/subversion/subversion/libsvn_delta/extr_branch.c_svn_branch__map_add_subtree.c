#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {scalar_t__ root_eid; int /*<<< orphan*/  e_map; } ;
typedef  TYPE_1__ svn_element__tree_t ;
struct TYPE_14__ {scalar_t__ parent_eid; char* name; int /*<<< orphan*/  payload; } ;
typedef  TYPE_2__ svn_element__content_t ;
struct TYPE_15__ {int /*<<< orphan*/  txn; } ;
typedef  TYPE_3__ svn_branch__state_t ;
typedef  int svn_branch__eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * branch_state_set_element (TYPE_3__*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_branch__txn_new_eid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int svn_eid__hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_element__content_create (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_element__tree_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_element__tree_get (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
svn_branch__map_add_subtree(svn_branch__state_t *to_branch,
                            int to_eid,
                            svn_branch__eid_t new_parent_eid,
                            const char *new_name,
                            svn_element__tree_t *new_subtree,
                            apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  svn_element__content_t *new_root_content;

  /* Get a new EID for the root element, if not given. */
  if (to_eid == -1)
    {
      SVN_ERR(svn_branch__txn_new_eid(to_branch->txn, &to_eid,
                                      scratch_pool));
    }

  /* Create the new subtree root element */
  new_root_content = svn_element__tree_get(new_subtree, new_subtree->root_eid);
  new_root_content = svn_element__content_create(new_parent_eid, new_name,
                                                 new_root_content->payload,
                                                 scratch_pool);
  SVN_ERR(branch_state_set_element(to_branch, to_eid, new_root_content,
                                   scratch_pool));

  /* Process its immediate children */
  for (hi = apr_hash_first(scratch_pool, new_subtree->e_map);
       hi; hi = apr_hash_next(hi))
    {
      int this_from_eid = svn_eid__hash_this_key(hi);
      svn_element__content_t *from_element = apr_hash_this_val(hi);

      if (from_element->parent_eid == new_subtree->root_eid)
        {
          svn_element__tree_t *this_subtree;

          /* Recurse. (We don't try to check whether it's a directory node,
             as we might not have the node kind in the map.) */
          this_subtree
            = svn_element__tree_create(new_subtree->e_map, this_from_eid,
                                       scratch_pool);
          SVN_ERR(svn_branch__map_add_subtree(to_branch, -1 /*to_eid*/,
                                              to_eid, from_element->name,
                                              this_subtree, scratch_pool));
        }
    }

  return SVN_NO_ERROR;
}