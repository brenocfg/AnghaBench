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
struct TYPE_4__ {scalar_t__ kind; scalar_t__ action; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct copy_warning_notify_baton {scalar_t__ depth; scalar_t__ warned; int /*<<< orphan*/  wrapped_baton; int /*<<< orphan*/  (* wrapped_func ) (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/  svn_depth_to_word (scalar_t__) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_wc_notify_commit_copied ; 
 scalar_t__ svn_wc_notify_commit_copied_replaced ; 

__attribute__((used)) static void
copy_warning_notify_func(void *baton,
                         const svn_wc_notify_t *notify,
                         apr_pool_t *pool)
{
  struct copy_warning_notify_baton *b = baton;

  /* Call the wrapped notification system (if any). */
  if (b->wrapped_func)
    b->wrapped_func(b->wrapped_baton, notify, pool);

  /* If we're being notified about a copy of a directory when our
     commit depth is less-than-infinite, and we've not already warned
     about this situation, then warn about it (and remember that we
     now have.)  */
  if ((! b->warned)
      && (b->depth < svn_depth_infinity)
      && (notify->kind == svn_node_dir)
      && ((notify->action == svn_wc_notify_commit_copied) ||
          (notify->action == svn_wc_notify_commit_copied_replaced)))
    {
      svn_error_t *err;
      err = svn_cmdline_printf(pool,
                               _("svn: The depth of this commit is '%s', "
                                 "but copies are always performed "
                                 "recursively in the repository.\n"),
                               svn_depth_to_word(b->depth));
      /* ### FIXME: Try to return this error showhow? */
      svn_error_clear(err);

      /* We'll only warn once. */
      b->warned = TRUE;
    }
}