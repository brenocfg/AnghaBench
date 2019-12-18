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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_file_options_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_blame_receiver2_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct blame_receiver_wrapper_baton2 {void* baton; int /*<<< orphan*/  receiver; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  blame_wrapper_receiver2 ; 
 int /*<<< orphan*/ * svn_client_blame5 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blame_receiver_wrapper_baton2*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_blame4(const char *target,
                  const svn_opt_revision_t *peg_revision,
                  const svn_opt_revision_t *start,
                  const svn_opt_revision_t *end,
                  const svn_diff_file_options_t *diff_options,
                  svn_boolean_t ignore_mime_type,
                  svn_boolean_t include_merged_revisions,
                  svn_client_blame_receiver2_t receiver,
                  void *receiver_baton,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *pool)
{
  struct blame_receiver_wrapper_baton2 baton;

  baton.receiver = receiver;
  baton.baton = receiver_baton;

  return svn_client_blame5(target, peg_revision, start, end, diff_options,
                           ignore_mime_type, include_merged_revisions,
                           blame_wrapper_receiver2, &baton, ctx, pool);
}