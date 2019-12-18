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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_4__ {scalar_t__ rev; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_history_as_mergeinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_wc_or_repos_mergeinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__wc_node_get_origin (TYPE_1__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_full_mergeinfo(svn_mergeinfo_t *recorded_mergeinfo,
                   svn_mergeinfo_t *implicit_mergeinfo,
                   svn_boolean_t *inherited,
                   svn_mergeinfo_inheritance_t inherit,
                   svn_ra_session_t *ra_session,
                   const char *target_abspath,
                   svn_revnum_t start,
                   svn_revnum_t end,
                   svn_client_ctx_t *ctx,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  /* First, we get the real mergeinfo. */
  if (recorded_mergeinfo)
    {
      SVN_ERR(svn_client__get_wc_or_repos_mergeinfo(recorded_mergeinfo,
                                                    inherited,
                                                    NULL /* from_repos */,
                                                    FALSE,
                                                    inherit, ra_session,
                                                    target_abspath,
                                                    ctx, result_pool));
    }

  if (implicit_mergeinfo)
    {
      svn_client__pathrev_t *target;

      /* Assert that we have sane input. */
      SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(start) && SVN_IS_VALID_REVNUM(end)
                     && (start > end));

      /* Retrieve the origin (original_*) of the node, or just the
         url if the node was not copied. */
      SVN_ERR(svn_client__wc_node_get_origin(&target, target_abspath, ctx,
                                             scratch_pool, scratch_pool));

      if (! target)
        {
          /* We've been asked to operate on a locally added target, so its
           * implicit mergeinfo is empty. */
          *implicit_mergeinfo = apr_hash_make(result_pool);
        }
      else if (target->rev <= end)
        {
          /* We're asking about a range outside our natural history
             altogether.  That means our implicit mergeinfo is empty. */
          *implicit_mergeinfo = apr_hash_make(result_pool);
        }
      else
        {
          /* Fetch so-called "implicit mergeinfo" (that is, natural
             history). */

          /* Do not ask for implicit mergeinfo from TARGET_ABSPATH's future.
             TARGET_ABSPATH might not even exist, and even if it does the
             working copy is *at* TARGET_REV so its implicit history ends
             at TARGET_REV! */
          if (target->rev < start)
            start = target->rev;

          /* Fetch the implicit mergeinfo. */
          SVN_ERR(svn_client__get_history_as_mergeinfo(implicit_mergeinfo,
                                                       NULL,
                                                       target, start, end,
                                                       ra_session, ctx,
                                                       result_pool));
        }
    } /*if (implicit_mergeinfo) */

  return SVN_NO_ERROR;
}