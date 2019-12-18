#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct node_baton {int dir_depth; int /*<<< orphan*/  filtered; int /*<<< orphan*/ * wrapped_baton; void* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct node_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct node_baton *
make_node_baton(void *edit_baton,
                svn_boolean_t filtered,
                int dir_depth,
                apr_pool_t *pool)
{
  struct node_baton *b = apr_palloc(pool, sizeof(*b));
  b->edit_baton = edit_baton;
  b->wrapped_baton = NULL;
  b->filtered = filtered;
  b->dir_depth = dir_depth;
  return b;
}