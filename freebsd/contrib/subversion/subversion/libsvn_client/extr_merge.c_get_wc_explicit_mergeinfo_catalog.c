#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
struct TYPE_21__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_22__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_5__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_INVALID_MERGEINFO_NO_MERGETRACKING ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_propget5 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_mergeinfo_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_opt_revision_working ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__externals_defined_below (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_wc_explicit_mergeinfo_catalog(apr_hash_t **subtrees_with_mergeinfo,
                                  const char *target_abspath,
                                  svn_depth_t depth,
                                  svn_client_ctx_t *ctx,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)
{
  svn_opt_revision_t working_revision = { svn_opt_revision_working, { 0 } };
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_hash_index_t *hi;
  apr_hash_t *externals;

  SVN_ERR(svn_client_propget5(subtrees_with_mergeinfo, NULL,
                              SVN_PROP_MERGEINFO, target_abspath,
                              &working_revision, &working_revision, NULL,
                              depth, NULL, ctx, result_pool, scratch_pool));

  SVN_ERR(svn_wc__externals_defined_below(&externals, ctx->wc_ctx,
                                          target_abspath, scratch_pool,
                                          scratch_pool));

  /* Convert property values to svn_mergeinfo_t. */
  for (hi = apr_hash_first(scratch_pool, *subtrees_with_mergeinfo);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *wc_path = apr_hash_this_key(hi);
      svn_string_t *mergeinfo_string = apr_hash_this_val(hi);
      svn_mergeinfo_t mergeinfo;
      svn_error_t *err;

      /* svn_client_propget5 picks up file externals with
         mergeinfo, but we don't want those. */
      if (svn_hash_gets(externals, wc_path))
        {
          svn_hash_sets(*subtrees_with_mergeinfo, wc_path, NULL);
          continue;
        }

      svn_pool_clear(iterpool);

      err = svn_mergeinfo_parse(&mergeinfo, mergeinfo_string->data,
                                result_pool);
      if (err)
        {
          if (err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
            {
              err = svn_error_createf(
                SVN_ERR_CLIENT_INVALID_MERGEINFO_NO_MERGETRACKING, err,
                _("Invalid mergeinfo detected on '%s', "
                  "merge tracking not possible"),
                svn_dirent_local_style(wc_path, scratch_pool));
            }
          return svn_error_trace(err);
        }
      svn_hash_sets(*subtrees_with_mergeinfo, wc_path, mergeinfo);
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}