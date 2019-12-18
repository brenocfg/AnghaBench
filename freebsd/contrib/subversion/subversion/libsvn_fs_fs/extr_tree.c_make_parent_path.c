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
struct TYPE_5__ {char* entry; int /*<<< orphan*/ * copy_src_path; int /*<<< orphan*/  copy_inherit; struct TYPE_5__* parent; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_id_inherit_unknown ; 

__attribute__((used)) static parent_path_t *
make_parent_path(dag_node_t *node,
                 char *entry,
                 parent_path_t *parent,
                 apr_pool_t *pool)
{
  parent_path_t *parent_path = apr_pcalloc(pool, sizeof(*parent_path));
  parent_path->node = node;
  parent_path->entry = entry;
  parent_path->parent = parent;
  parent_path->copy_inherit = copy_id_inherit_unknown;
  parent_path->copy_src_path = NULL;
  return parent_path;
}