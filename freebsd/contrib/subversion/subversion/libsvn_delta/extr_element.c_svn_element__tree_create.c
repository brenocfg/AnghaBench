#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int root_eid; int /*<<< orphan*/  e_map; } ;
typedef  TYPE_1__ svn_element__tree_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_element__tree_t *
svn_element__tree_create(apr_hash_t *e_map,
                         int root_eid,
                         apr_pool_t *result_pool)
{
  svn_element__tree_t *element_tree
    = apr_pcalloc(result_pool, sizeof(*element_tree));

  element_tree->e_map = e_map ? apr_hash_copy(result_pool, e_map)
                              : apr_hash_make(result_pool);
  element_tree->root_eid = root_eid;
  return element_tree;
}