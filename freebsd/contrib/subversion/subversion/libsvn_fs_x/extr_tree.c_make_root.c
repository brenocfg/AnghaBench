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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/ * vtable; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  root_vtable ; 

__attribute__((used)) static svn_fs_root_t *
make_root(svn_fs_t *fs,
          apr_pool_t *result_pool)
{
  svn_fs_root_t *root = apr_pcalloc(result_pool, sizeof(*root));

  root->fs = fs;
  root->pool = result_pool;
  root->vtable = &root_vtable;

  return root;
}