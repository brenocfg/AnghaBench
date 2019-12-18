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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_PROPS_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,char*,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checked_in_props ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_get_value (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_ra_serf__fetch_node_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__fetch_dav_prop(const char **value,
                            svn_ra_serf__session_t *session,
                            const char *url,
                            svn_revnum_t revision,
                            const char *propname,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  apr_hash_t *props;
  apr_hash_t *dav_props;

  SVN_ERR(svn_ra_serf__fetch_node_props(&props, session, url, revision,
                                        checked_in_props,
                                        scratch_pool, scratch_pool));
  dav_props = apr_hash_get(props, "DAV:", 4);
  if (dav_props == NULL)
    return svn_error_create(SVN_ERR_RA_DAV_PROPS_NOT_FOUND, NULL,
                            _("The PROPFIND response did not include "
                              "the requested 'DAV:' properties"));

  /* We wouldn't get here if the resource was not found (404), so the
     property should be present.

     Note: it is okay to call apr_pstrdup() with NULL.  */
  *value = apr_pstrdup(result_pool, svn_prop_get_value(dav_props, propname));

  return SVN_NO_ERROR;
}