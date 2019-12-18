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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char* SVN_DAV__VERSION_NAME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_PROPS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  baseline_props ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_serf__fetch_node_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_urlpath__canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
retrieve_baseline_info(svn_revnum_t *actual_revision,
                       const char **basecoll_url_p,
                       svn_ra_serf__session_t *session,
                       const char *baseline_url,
                       svn_revnum_t revision,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  apr_hash_t *props;
  apr_hash_t *dav_props;
  const char *basecoll_url;

  SVN_ERR(svn_ra_serf__fetch_node_props(&props, session,
                                        baseline_url, revision,
                                        baseline_props,
                                        scratch_pool, scratch_pool));
  dav_props = apr_hash_get(props, "DAV:", 4);
  /* If DAV_PROPS is NULL, then svn_prop_get_value() will return NULL.  */

  basecoll_url = svn_prop_get_value(dav_props, "baseline-collection");
  if (!basecoll_url)
    {
      return svn_error_create(SVN_ERR_RA_DAV_PROPS_NOT_FOUND, NULL,
                              _("The PROPFIND response did not include "
                                "the requested baseline-collection value"));
    }
  *basecoll_url_p = svn_urlpath__canonicalize(basecoll_url, result_pool);

  if (actual_revision)
    {
      const char *version_name;

      version_name = svn_prop_get_value(dav_props, SVN_DAV__VERSION_NAME);
      if (version_name)
        {
          apr_int64_t rev;

          SVN_ERR(svn_cstring_atoi64(&rev, version_name));
          *actual_revision = (svn_revnum_t)rev;
        }

      if (!version_name || !SVN_IS_VALID_REVNUM(*actual_revision))
        return svn_error_create(SVN_ERR_RA_DAV_PROPS_NOT_FOUND, NULL,
                                _("The PROPFIND response did not include "
                                  "the requested version-name value"));
    }

  return SVN_NO_ERROR;
}