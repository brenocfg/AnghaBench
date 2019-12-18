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
typedef  int /*<<< orphan*/  svn_repos_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {scalar_t__ skipped; struct parse_baton* pb; } ;
struct parse_baton {int /*<<< orphan*/  notify_pool; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct node_baton {struct revision_baton* rb; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_notify_load_node_done ; 

__attribute__((used)) static svn_error_t *
close_node(void *baton)
{
  struct node_baton *nb = baton;
  struct revision_baton *rb = nb->rb;
  struct parse_baton *pb = rb->pb;

  /* If we're skipping this revision, we're done here. */
  if (rb->skipped)
    return SVN_NO_ERROR;

  if (pb->notify_func)
    {
      /* ### TODO: Use proper scratch pool instead of pb->notify_pool */
      svn_repos_notify_t *notify = svn_repos_notify_create(
                                            svn_repos_notify_load_node_done,
                                            pb->notify_pool);

      pb->notify_func(pb->notify_baton, notify, pb->notify_pool);
      svn_pool_clear(pb->notify_pool);
    }

  return SVN_NO_ERROR;
}