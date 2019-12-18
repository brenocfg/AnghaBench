#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_client_switch2 (int /*<<< orphan*/ *,char const*,char const*,TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_opt_revision_unspecified ; 

svn_error_t *
svn_client_switch(svn_revnum_t *result_rev,
                  const char *path,
                  const char *switch_url,
                  const svn_opt_revision_t *revision,
                  svn_boolean_t recurse,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *pool)
{
  svn_opt_revision_t peg_revision;
  peg_revision.kind = svn_opt_revision_unspecified;
  return svn_client_switch2(result_rev, path, switch_url,
                            &peg_revision, revision,
                            SVN_DEPTH_INFINITY_OR_FILES(recurse),
                            FALSE, FALSE, FALSE, ctx, pool);
}