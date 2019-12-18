#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_prefix_tree__t ;
struct TYPE_8__ {int sub_node_count; struct TYPE_8__** sub_nodes; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 void* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__**,TYPE_2__**,int) ; 

__attribute__((used)) static void
auto_realloc_sub_nodes(svn_prefix_tree__t *tree,
                       node_t *node)
{
  if (node->sub_node_count & (node->sub_node_count - 1))
    return;

  if (node->sub_node_count == 0)
    {
      node->sub_nodes = apr_pcalloc(tree->pool, sizeof(*node->sub_nodes));
    }
  else
    {
      node_t **sub_nodes
        = apr_pcalloc(tree->pool,
                      2 * node->sub_node_count * sizeof(*sub_nodes));
      memcpy(sub_nodes, node->sub_nodes,
             node->sub_node_count * sizeof(*sub_nodes));
      node->sub_nodes = sub_nodes;
    }
}