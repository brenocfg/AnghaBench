#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_18__ {scalar_t__ kind; } ;
typedef  TYPE_5__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int svn_boolean_t ;
struct TYPE_19__ {int is_reintegrate_like; TYPE_4__* yca; TYPE_3__* target; TYPE_2__* right; TYPE_1__* base; } ;
typedef  TYPE_6__ automatic_merge_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
struct TYPE_16__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
struct TYPE_15__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
struct TYPE_14__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_find_automatic_merge (TYPE_6__**,char const*,TYPE_5__ const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_automatic_merge_no_wc (TYPE_6__**,char const*,TYPE_5__ const*,char const*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_opt_revision_base ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_opt_revision_working ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 

svn_error_t *
svn_client_get_merging_summary(svn_boolean_t *needs_reintegration,
                               const char **yca_url, svn_revnum_t *yca_rev,
                               const char **base_url, svn_revnum_t *base_rev,
                               const char **right_url, svn_revnum_t *right_rev,
                               const char **target_url, svn_revnum_t *target_rev,
                               const char **repos_root_url,
                               const char *source_path_or_url,
                               const svn_opt_revision_t *source_revision,
                               const char *target_path_or_url,
                               const svn_opt_revision_t *target_revision,
                               svn_client_ctx_t *ctx,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  svn_boolean_t target_is_wc;
  automatic_merge_t *merge;

  target_is_wc = (! svn_path_is_url(target_path_or_url))
                 && (target_revision->kind == svn_opt_revision_unspecified
                     || target_revision->kind == svn_opt_revision_working
                     || target_revision->kind == svn_opt_revision_base);
  if (target_is_wc)
    {
      const char *target_abspath;

      SVN_ERR(svn_dirent_get_absolute(&target_abspath, target_path_or_url,
                                      scratch_pool));
      SVN_ERR(client_find_automatic_merge(
                &merge,
                source_path_or_url, source_revision,
                target_abspath,
                TRUE, TRUE, TRUE,  /* allow_* */
                ctx, scratch_pool, scratch_pool));
    }
  else
    SVN_ERR(find_automatic_merge_no_wc(
              &merge,
              source_path_or_url, source_revision,
              target_path_or_url, target_revision,
              ctx, scratch_pool, scratch_pool));

  if (needs_reintegration)
    *needs_reintegration = merge->is_reintegrate_like;
  if (yca_url)
    *yca_url = apr_pstrdup(result_pool, merge->yca->url);
  if (yca_rev)
    *yca_rev = merge->yca->rev;
  if (base_url)
    *base_url = apr_pstrdup(result_pool, merge->base->url);
  if (base_rev)
    *base_rev = merge->base->rev;
  if (right_url)
    *right_url = apr_pstrdup(result_pool, merge->right->url);
  if (right_rev)
    *right_rev = merge->right->rev;
  if (target_url)
    *target_url = apr_pstrdup(result_pool, merge->target->url);
  if (target_rev)
    *target_rev = merge->target->rev;
  if (repos_root_url)
    *repos_root_url = apr_pstrdup(result_pool, merge->yca->repos_root_url);

  return SVN_NO_ERROR;
}