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
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {scalar_t__ rev; int /*<<< orphan*/  txn_root; scalar_t__ skipped; struct parse_baton* pb; } ;
struct parse_baton {int /*<<< orphan*/  notify_pool; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct node_baton {int action; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_MALFORMED_DATA ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_UNRECOGNIZED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  make_node_baton (struct node_baton**,int /*<<< orphan*/ *,struct revision_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maybe_add_with_history (struct node_baton*,struct revision_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  svn_node_action_add 131 
#define  svn_node_action_change 130 
#define  svn_node_action_delete 129 
#define  svn_node_action_replace 128 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_notify_load_node_start ; 

__attribute__((used)) static svn_error_t *
new_node_record(void **node_baton,
                apr_hash_t *headers,
                void *revision_baton,
                apr_pool_t *pool)
{
  struct revision_baton *rb = revision_baton;
  struct parse_baton *pb = rb->pb;
  struct node_baton *nb;

  if (rb->rev == 0)
    return svn_error_create(SVN_ERR_STREAM_MALFORMED_DATA, NULL,
                            _("Malformed dumpstream: "
                              "Revision 0 must not contain node records"));

  SVN_ERR(make_node_baton(&nb, headers, rb, pool));

  /* If we're skipping this revision, we're done here. */
  if (rb->skipped)
    {
      *node_baton = nb;
      return SVN_NO_ERROR;
    }

  /* Make sure we have an action we recognize. */
  if (nb->action < svn_node_action_change
        || nb->action > svn_node_action_replace)
      return svn_error_createf(SVN_ERR_STREAM_UNRECOGNIZED_DATA, NULL,
                               _("Unrecognized node-action on node '%s'"),
                               nb->path);

  if (pb->notify_func)
    {
      /* ### TODO: Use proper scratch pool instead of pb->notify_pool */
      svn_repos_notify_t *notify = svn_repos_notify_create(
                                        svn_repos_notify_load_node_start,
                                        pb->notify_pool);

      notify->path = nb->path;
      pb->notify_func(pb->notify_baton, notify, pb->notify_pool);
      svn_pool_clear(pb->notify_pool);
    }

  switch (nb->action)
    {
    case svn_node_action_change:
      break;

    case svn_node_action_delete:
      SVN_ERR(svn_fs_delete(rb->txn_root, nb->path, pool));
      break;

    case svn_node_action_add:
      SVN_ERR(maybe_add_with_history(nb, rb, pool));
      break;

    case svn_node_action_replace:
      SVN_ERR(svn_fs_delete(rb->txn_root, nb->path, pool));
      SVN_ERR(maybe_add_with_history(nb, rb, pool));
      break;
    }

  *node_baton = nb;
  return SVN_NO_ERROR;
}