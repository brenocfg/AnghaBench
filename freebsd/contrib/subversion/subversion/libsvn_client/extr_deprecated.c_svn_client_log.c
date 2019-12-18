#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int number; } ;
struct TYPE_15__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  (* svn_log_message_receiver_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NO_SUCH_REVISION ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* svn_client_log2 (int /*<<< orphan*/  const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_number ; 

svn_error_t *
svn_client_log(const apr_array_header_t *targets,
               const svn_opt_revision_t *start,
               const svn_opt_revision_t *end,
               svn_boolean_t discover_changed_paths,
               svn_boolean_t strict_node_history,
               svn_log_message_receiver_t receiver,
               void *receiver_baton,
               svn_client_ctx_t *ctx,
               apr_pool_t *pool)
{
  svn_error_t *err = SVN_NO_ERROR;

  err = svn_client_log2(targets, start, end, 0, discover_changed_paths,
                        strict_node_history, receiver, receiver_baton, ctx,
                        pool);

  /* Special case: If there have been no commits, we'll get an error
   * for requesting log of a revision higher than 0.  But the
   * default behavior of "svn log" is to give revisions HEAD through
   * 1, on the assumption that HEAD >= 1.
   *
   * So if we got that error for that reason, and it looks like the
   * user was just depending on the defaults (rather than explicitly
   * requesting the log for revision 1), then we don't error.  Instead
   * we just invoke the receiver manually on a hand-constructed log
   * message for revision 0.
   *
   * See also http://subversion.tigris.org/issues/show_bug.cgi?id=692.
   */
  if (err && (err->apr_err == SVN_ERR_FS_NO_SUCH_REVISION)
      && (start->kind == svn_opt_revision_head)
      && ((end->kind == svn_opt_revision_number)
          && (end->value.number == 1)))
    {

      /* We don't need to check if HEAD is 0, because that must be the case,
       * by logical deduction: The revision range specified is HEAD:1.
       * HEAD cannot not exist, so the revision to which "no such revision"
       * applies is 1. If revision 1 does not exist, then HEAD is 0.
       * Hence, we deduce the repository is empty without needing access
       * to further information. */

      svn_error_clear(err);
      err = SVN_NO_ERROR;

      /* Log receivers are free to handle revision 0 specially... But
         just in case some don't, we make up a message here. */
      SVN_ERR(receiver(receiver_baton,
                       NULL, 0, "", "", _("No commits in repository"),
                       pool));
    }

  return svn_error_trace(err);
}