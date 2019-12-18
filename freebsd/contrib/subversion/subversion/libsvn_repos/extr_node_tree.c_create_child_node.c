#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* child; } ;
typedef  TYPE_1__ svn_repos_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* create_node (char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_sibling_node (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_repos_node_t *
create_child_node(svn_repos_node_t *parent,
                  const char *name,
                  apr_pool_t *pool)
{
  /* No PARENT node?  That's just not gonna work out. */
  if (! parent)
    return NULL;

  /* If PARENT has no children, create its first one and return that. */
  if (! parent->child)
    return (parent->child = create_node(name, parent, pool));

  /* If PARENT already has a child, create a new sibling for its first
     child and return that. */
  return create_sibling_node(parent->child, name, pool);
}