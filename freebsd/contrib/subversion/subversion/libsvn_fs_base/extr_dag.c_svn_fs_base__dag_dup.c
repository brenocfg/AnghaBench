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
struct TYPE_5__ {int /*<<< orphan*/  created_path; int /*<<< orphan*/  kind; int /*<<< orphan*/  id; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

dag_node_t *
svn_fs_base__dag_dup(const dag_node_t *node,
                     apr_pool_t *pool)
{
  /* Allocate our new node. */
  dag_node_t *new_node = apr_pcalloc(pool, sizeof(*new_node));

  new_node->fs = node->fs;
  new_node->id = svn_fs_base__id_copy(node->id, pool);
  new_node->kind = node->kind;
  new_node->created_path = apr_pstrdup(pool, node->created_path);
  return new_node;
}