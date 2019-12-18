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
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_fs_root_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

void
svn_fs_close_root(svn_fs_root_t *root)
{
  svn_pool_destroy(root->pool);
}