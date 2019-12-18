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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
struct conflict_walker_baton {scalar_t__ quit; int /*<<< orphan*/  ctx; int /*<<< orphan*/  conflict_stats; int /*<<< orphan*/  pb; int /*<<< orphan*/  path_prefix; int /*<<< orphan*/  editor_cmd; int /*<<< orphan*/  accept_which; int /*<<< orphan*/  printed_summary; int /*<<< orphan*/  external_failed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CANCELLED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_cl__resolve_conflict (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
conflict_walker(void *baton, svn_client_conflict_t *conflict,
                apr_pool_t *scratch_pool)
{
  struct conflict_walker_baton *cwb = baton;

  SVN_ERR(svn_cl__resolve_conflict(&cwb->quit, &cwb->external_failed,
                                   &cwb->printed_summary, conflict,
                                   cwb->accept_which, cwb->editor_cmd,
                                   cwb->path_prefix, cwb->pb,
                                   cwb->conflict_stats,
                                   cwb->ctx, scratch_pool));
  if (cwb->quit)
    return svn_error_create(SVN_ERR_CANCELLED, NULL, NULL);

  return SVN_NO_ERROR;
}