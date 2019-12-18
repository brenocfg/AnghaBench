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
struct TYPE_3__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_commit_info_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_client_move2 (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_unspecified ; 

svn_error_t *
svn_client_move(svn_client_commit_info_t **commit_info_p,
                const char *src_path,
                const svn_opt_revision_t *src_revision,
                const char *dst_path,
                svn_boolean_t force,
                svn_client_ctx_t *ctx,
                apr_pool_t *pool)
{
  /* It doesn't make sense to specify revisions in a move. */

  /* ### todo: this check could fail wrongly.  For example,
     someone could pass in an svn_opt_revision_number that just
     happens to be the HEAD.  It's fair enough to punt then, IMHO,
     and just demand that the user not specify a revision at all;
     beats mucking up this function with RA calls and such. */
  if (src_revision->kind != svn_opt_revision_unspecified
      && src_revision->kind != svn_opt_revision_head)
    {
      return svn_error_create
        (SVN_ERR_UNSUPPORTED_FEATURE, NULL,
         _("Cannot specify revisions (except HEAD) with move operations"));
    }

  return svn_client_move2(commit_info_p, src_path, dst_path, force, ctx, pool);
}