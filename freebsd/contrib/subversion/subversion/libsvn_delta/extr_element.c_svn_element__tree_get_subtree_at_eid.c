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
struct TYPE_9__ {int /*<<< orphan*/  root_eid; int /*<<< orphan*/  e_map; } ;
typedef  TYPE_1__ svn_element__tree_t ;
struct TYPE_10__ {int /*<<< orphan*/  payload; } ;
typedef  TYPE_2__ svn_element__content_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_element__content_create (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_element__tree_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_element__tree_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_element__tree_purge_orphans (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_element__tree_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_element__tree_t *
svn_element__tree_get_subtree_at_eid(svn_element__tree_t *element_tree,
                                     int eid,
                                     apr_pool_t *result_pool)
{
  svn_element__tree_t *new_subtree;
  svn_element__content_t *subtree_root_element;

  new_subtree = svn_element__tree_create(element_tree->e_map, eid,
                                         result_pool);

  /* Purge orphans */
  svn_element__tree_purge_orphans(new_subtree->e_map,
                                  new_subtree->root_eid, result_pool);

  /* Remove 'parent' and 'name' attributes from subtree root element */
  subtree_root_element
    = svn_element__tree_get(new_subtree, new_subtree->root_eid);
  svn_element__tree_set(new_subtree, new_subtree->root_eid,
                        svn_element__content_create(
                          -1, "", subtree_root_element->payload, result_pool));

  return new_subtree;
}