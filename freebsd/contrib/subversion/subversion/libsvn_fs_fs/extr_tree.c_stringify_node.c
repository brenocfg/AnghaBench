#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {char const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_fs_fs__id_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
stringify_node(dag_node_t *node,
               apr_pool_t *pool)
{
  /* ### TODO: print some PATH@REV to it, too. */
  return svn_fs_fs__id_unparse(svn_fs_fs__dag_get_id(node), pool)->data;
}