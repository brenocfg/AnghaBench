#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  abspath; scalar_t__ implicit_mergeinfo; } ;
typedef  TYPE_1__ svn_client__merge_path_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_full_mergeinfo (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inherit_implicit_mergeinfo_from_parent (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_inherited ; 

__attribute__((used)) static svn_error_t *
ensure_implicit_mergeinfo(svn_client__merge_path_t *parent,
                          svn_client__merge_path_t *child,
                          svn_boolean_t child_inherits_parent,
                          svn_revnum_t revision1,
                          svn_revnum_t revision2,
                          svn_ra_session_t *ra_session,
                          svn_client_ctx_t *ctx,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  /* If we haven't already found CHILD->IMPLICIT_MERGEINFO then
     contact the server to get it. */

  if (child->implicit_mergeinfo)
    return SVN_NO_ERROR;

  if (child_inherits_parent)
    SVN_ERR(inherit_implicit_mergeinfo_from_parent(parent,
                                                   child,
                                                   revision1,
                                                   revision2,
                                                   ra_session,
                                                   ctx,
                                                   result_pool,
                                                   scratch_pool));
  else
    SVN_ERR(get_full_mergeinfo(NULL,
                               &(child->implicit_mergeinfo),
                               NULL, svn_mergeinfo_inherited,
                               ra_session, child->abspath,
                               MAX(revision1, revision2),
                               MIN(revision1, revision2),
                               ctx, result_pool, scratch_pool));

  return SVN_NO_ERROR;
}