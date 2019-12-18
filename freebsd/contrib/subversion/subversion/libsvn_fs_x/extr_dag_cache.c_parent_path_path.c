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
struct TYPE_3__ {int /*<<< orphan*/  entry; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ svn_fs_x__dag_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* svn_fspath__join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
parent_path_path(svn_fs_x__dag_path_t *dag_path,
                 apr_pool_t *pool)
{
  const char *path_so_far = "/";
  if (dag_path->parent)
    path_so_far = parent_path_path(dag_path->parent, pool);
  return dag_path->entry
    ? svn_fspath__join(path_so_far, dag_path->entry, pool)
    : path_so_far;
}