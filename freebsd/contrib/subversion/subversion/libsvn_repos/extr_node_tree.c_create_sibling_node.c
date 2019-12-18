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
struct TYPE_5__ {int /*<<< orphan*/  parent; struct TYPE_5__* sibling; } ;
typedef  TYPE_1__ svn_repos_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* create_node (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_repos_node_t *
create_sibling_node(svn_repos_node_t *elder,
                    const char *name,
                    apr_pool_t *pool)
{
  svn_repos_node_t *tmp_node;

  /* No ELDER sibling?  That's just not gonna work out. */
  if (! elder)
    return NULL;

  /* Run to the end of the list of siblings of ELDER. */
  tmp_node = elder;
  while (tmp_node->sibling)
    tmp_node = tmp_node->sibling;

  /* Create a new youngest sibling and return that. */
  return (tmp_node->sibling = create_node(name, elder->parent, pool));
}