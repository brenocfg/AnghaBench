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
struct TYPE_4__ {struct TYPE_4__* sibling; int /*<<< orphan*/  name; struct TYPE_4__* child; } ;
typedef  TYPE_1__ svn_repos_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_repos_node_t *
find_child_by_name(svn_repos_node_t *parent,
                   const char *name)
{
  svn_repos_node_t *tmp_node;

  /* No PARENT node, or a barren PARENT?  Nothing to find. */
  if ((! parent) || (! parent->child))
    return NULL;

  /* Look through the children for a node with a matching name. */
  tmp_node = parent->child;
  while (1)
    {
      if (! strcmp(tmp_node->name, name))
        {
          return tmp_node;
        }
      else
        {
          if (tmp_node->sibling)
            tmp_node = tmp_node->sibling;
          else
            break;
        }
    }

  return NULL;
}