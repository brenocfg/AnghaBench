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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_baton {TYPE_1__* node; int /*<<< orphan*/ * parent_baton; struct edit_baton* edit_baton; } ;
struct edit_baton {int /*<<< orphan*/  node_pool; TYPE_1__* node; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {char action; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct node_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* create_node (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_dir ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **root_baton)
{
  struct edit_baton *eb = edit_baton;
  struct node_baton *d = apr_pcalloc(pool, sizeof(*d));

  d->edit_baton = eb;
  d->parent_baton = NULL;
  d->node = (eb->node = create_node("", NULL, eb->node_pool));
  d->node->kind = svn_node_dir;
  d->node->action = 'R';
  *root_baton = d;

  return SVN_NO_ERROR;
}