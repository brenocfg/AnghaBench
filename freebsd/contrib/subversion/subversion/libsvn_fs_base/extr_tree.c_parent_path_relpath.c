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
struct TYPE_4__ {struct TYPE_4__* parent; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ parent_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
parent_path_relpath(parent_path_t *child,
                    parent_path_t *ancestor,
                    apr_pool_t *pool)
{
  const char *path_so_far = "";
  parent_path_t *this_node = child;
  while (this_node != ancestor)
    {
      assert(this_node != NULL);
      path_so_far = svn_relpath_join(this_node->entry, path_so_far, pool);
      this_node = this_node->parent;
    }
  return path_so_far;
}