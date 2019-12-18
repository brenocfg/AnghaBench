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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_prop_name (char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  propset_on_url (char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 

svn_error_t *
svn_client_propset_remote(const char *propname,
                          const svn_string_t *propval,
                          const char *url,
                          svn_boolean_t skip_checks,
                          svn_revnum_t base_revision_for_url,
                          const apr_hash_t *revprop_table,
                          svn_commit_callback2_t commit_callback,
                          void *commit_baton,
                          svn_client_ctx_t *ctx,
                          apr_pool_t *scratch_pool)
{
  if (!svn_path_is_url(url))
    return svn_error_create(SVN_ERR_ILLEGAL_TARGET, NULL,
                            _("Targets must be URLs"));

  SVN_ERR(check_prop_name(propname, propval));

  /* The rationale for requiring the base_revision_for_url
     argument is that without it, it's too easy to possibly
     overwrite someone else's change without noticing.  (See also
     tools/examples/svnput.c). */
  if (! SVN_IS_VALID_REVNUM(base_revision_for_url))
    return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                            _("Setting property on non-local targets "
                              "needs a base revision"));

  /* ### When you set svn:eol-style or svn:keywords on a wc file,
     ### Subversion sends a textdelta at commit time to properly
     ### normalize the file in the repository.  If we want to
     ### support editing these properties on URLs, then we should
     ### generate the same textdelta; for now, we won't support
     ### editing these properties on URLs.  (Admittedly, this
     ### means that all the machinery with get_file_for_validation
     ### is unused.)
   */
  if ((strcmp(propname, SVN_PROP_EOL_STYLE) == 0) ||
      (strcmp(propname, SVN_PROP_KEYWORDS) == 0))
    return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                             _("Setting property '%s' on non-local "
                               "targets is not supported"), propname);

  SVN_ERR(propset_on_url(propname, propval, url, skip_checks,
                         base_revision_for_url, revprop_table,
                         commit_callback, commit_baton, ctx, scratch_pool));

  return SVN_NO_ERROR;
}