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
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {TYPE_1__* pb; int /*<<< orphan*/  txn_root; scalar_t__ skipped; } ;
struct node_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; struct revision_baton* rb; } ;
struct TYPE_2__ {int /*<<< orphan*/  validate_props; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * change_node_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
delete_node_property(void *baton,
                     const char *name)
{
  struct node_baton *nb = baton;
  struct revision_baton *rb = nb->rb;

  /* If we're skipping this revision, we're done here. */
  if (rb->skipped)
    return SVN_NO_ERROR;

  return change_node_prop(rb->txn_root, nb->path, name, NULL,
                          rb->pb->validate_props, nb->pool);
}