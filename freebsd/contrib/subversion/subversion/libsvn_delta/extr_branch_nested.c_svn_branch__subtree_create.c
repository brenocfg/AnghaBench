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
struct TYPE_4__ {int /*<<< orphan*/  subbranches; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ svn_branch__subtree_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_element__tree_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

svn_branch__subtree_t *
svn_branch__subtree_create(apr_hash_t *e_map,
                           int root_eid,
                           apr_pool_t *result_pool)
{
  svn_branch__subtree_t *subtree = apr_pcalloc(result_pool, sizeof(*subtree));

  subtree->tree = svn_element__tree_create(e_map, root_eid, result_pool);
  subtree->subbranches = apr_hash_make(result_pool);
  return subtree;
}