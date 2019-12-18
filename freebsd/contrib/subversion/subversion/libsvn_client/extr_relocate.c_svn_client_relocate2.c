#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_17__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_18__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
struct validator_baton_t {char const* path; int /*<<< orphan*/ * pool; int /*<<< orphan*/  url_uuids; TYPE_2__* ctx; } ;
struct url_uuid_t {int dummy; } ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 size_t strlen (char*) ; 
 TYPE_1__* svn_client_get_repos_root (char const**,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__externals_defined_below (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__read_external_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_relocate4 (int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ ,struct validator_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validator_func ; 

svn_error_t *
svn_client_relocate2(const char *wcroot_dir,
                     const char *from_prefix,
                     const char *to_prefix,
                     svn_boolean_t ignore_externals,
                     svn_client_ctx_t *ctx,
                     apr_pool_t *pool)
{
  struct validator_baton_t vb;
  const char *local_abspath;
  apr_hash_t *externals_hash = NULL;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = NULL;
  const char *old_repos_root_url, *new_repos_root_url;
  char *sig_from_prefix, *sig_to_prefix;
  apr_size_t index_from, index_to;

  /* Populate our validator callback baton, and call the relocate code. */
  vb.ctx = ctx;
  vb.path = wcroot_dir;
  vb.url_uuids = apr_array_make(pool, 1, sizeof(struct url_uuid_t));
  vb.pool = pool;

  if (svn_path_is_url(wcroot_dir))
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a local path"),
                             wcroot_dir);

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, wcroot_dir, pool));

  /* If we're ignoring externals, just relocate and get outta here. */
  if (ignore_externals)
    {
      return svn_error_trace(svn_wc_relocate4(ctx->wc_ctx, local_abspath,
                                              from_prefix, to_prefix,
                                              validator_func, &vb, pool));
    }

  /* Fetch our current root URL. */
  SVN_ERR(svn_client_get_repos_root(&old_repos_root_url, NULL /* uuid */,
                                    local_abspath, ctx, pool, pool));

  /* Perform the relocation. */
  SVN_ERR(svn_wc_relocate4(ctx->wc_ctx, local_abspath, from_prefix, to_prefix,
                           validator_func, &vb, pool));

  /* Now fetch new current root URL. */
  SVN_ERR(svn_client_get_repos_root(&new_repos_root_url, NULL /* uuid */,
                                    local_abspath, ctx, pool, pool));


  /* Relocate externals, too (if any). */
  SVN_ERR(svn_wc__externals_defined_below(&externals_hash,
                                          ctx->wc_ctx, local_abspath,
                                          pool, pool));
  if (! apr_hash_count(externals_hash))
    return SVN_NO_ERROR;

  /* A valid prefix for the main working copy may be too long to be
     valid for an external.  Trim any common trailing characters to
     leave the significant part that changes. */
  sig_from_prefix = apr_pstrdup(pool, from_prefix);
  sig_to_prefix = apr_pstrdup(pool, to_prefix);
  index_from = strlen(sig_from_prefix);
  index_to = strlen(sig_to_prefix);
  while (index_from && index_to
         && sig_from_prefix[index_from] == sig_to_prefix[index_to])
    {
      sig_from_prefix[index_from] = sig_to_prefix[index_to] = '\0';
      --index_from;
      --index_to;
    }

  iterpool = svn_pool_create(pool);

  for (hi = apr_hash_first(pool, externals_hash);
       hi != NULL;
       hi = apr_hash_next(hi))
    {
      svn_node_kind_t kind;
      const char *this_abspath = apr_hash_this_key(hi);

      svn_pool_clear(iterpool);

      SVN_ERR(svn_wc__read_external_info(&kind, NULL, NULL, NULL, NULL,
                                         ctx->wc_ctx,
                                         local_abspath, this_abspath,
                                         FALSE, iterpool, iterpool));

      if (kind == svn_node_dir)
        {
          const char *this_repos_root_url;
          svn_error_t *err;

          err = svn_client_get_repos_root(&this_repos_root_url, NULL /* uuid */,
                                          this_abspath, ctx, iterpool, iterpool);

          /* Ignore externals that aren't present in the working copy.
           * This can happen if an external is deleted from disk accidentally,
           * or if an external is configured on a locally added directory. */
          if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
            {
              svn_error_clear(err);
              continue;
            }
          SVN_ERR(err);

          if (strcmp(old_repos_root_url, this_repos_root_url) == 0)
            SVN_ERR(svn_client_relocate2(this_abspath,
                                         sig_from_prefix, sig_to_prefix,
                                         FALSE /* ignore_externals */,
                                         ctx, iterpool));
        }
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}