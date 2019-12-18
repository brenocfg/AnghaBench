#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_3__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ dag_node_t ;

/* Variables and functions */

svn_fs_t *
svn_fs_fs__dag_get_fs(dag_node_t *node)
{
  return node->fs;
}