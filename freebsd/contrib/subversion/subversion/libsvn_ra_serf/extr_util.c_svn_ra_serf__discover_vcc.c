#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_16__ {char* path; } ;
struct TYPE_18__ {char* vcc_url; int /*<<< orphan*/  pool; void* uuid; TYPE_14__ repos_root; scalar_t__ repos_root_str; TYPE_14__ session_url; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
struct TYPE_19__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DAV_PROP_NS_DAV ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_ERR_RA_DAV_FORBIDDEN ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,char*,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  apr_uri_unparse (int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_props ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 scalar_t__ svn_fspath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_component_count (char const*) ; 
 int /*<<< orphan*/  svn_path_remove_components (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* svn_ra_serf__fetch_node_props (int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_urlpath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_urlpath__dirname (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__discover_vcc(const char **vcc_url,
                          svn_ra_serf__session_t *session,
                          apr_pool_t *scratch_pool)
{
  const char *path;
  const char *relative_path;
  const char *uuid;

  /* If we've already got the information our caller seeks, just return it.  */
  if (session->vcc_url && session->repos_root_str)
    {
      *vcc_url = session->vcc_url;
      return SVN_NO_ERROR;
    }

  path = session->session_url.path;
  *vcc_url = NULL;
  uuid = NULL;

  do
    {
      apr_hash_t *props;
      svn_error_t *err;

      err = svn_ra_serf__fetch_node_props(&props, session,
                                          path, SVN_INVALID_REVNUM,
                                          base_props,
                                          scratch_pool, scratch_pool);
      if (! err)
        {
          apr_hash_t *ns_props;

          ns_props = apr_hash_get(props, "DAV:", 4);
          *vcc_url = svn_prop_get_value(ns_props,
                                        "version-controlled-configuration");

          ns_props = svn_hash_gets(props, SVN_DAV_PROP_NS_DAV);
          relative_path = svn_prop_get_value(ns_props,
                                             "baseline-relative-path");
          uuid = svn_prop_get_value(ns_props, "repository-uuid");
          break;
        }
      else
        {
          if ((err->apr_err != SVN_ERR_FS_NOT_FOUND) &&
              (err->apr_err != SVN_ERR_RA_DAV_FORBIDDEN))
            {
              return svn_error_trace(err);  /* found a _real_ error */
            }
          else
            {
              /* This happens when the file is missing in HEAD. */
              svn_error_clear(err);

              /* Okay, strip off a component from PATH. */
              path = svn_urlpath__dirname(path, scratch_pool);
            }
        }
    }
  while ((path[0] != '\0')
         && (! (path[0] == '/' && path[1] == '\0')));

  if (!*vcc_url)
    {
      return svn_error_create(SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED, NULL,
                              _("The PROPFIND response did not include the "
                                "requested version-controlled-configuration "
                                "value"));
    }

  /* Store our VCC in our cache. */
  if (!session->vcc_url)
    {
      session->vcc_url = apr_pstrdup(session->pool, *vcc_url);
    }

  /* Update our cached repository root URL. */
  if (!session->repos_root_str)
    {
      svn_stringbuf_t *url_buf;

      url_buf = svn_stringbuf_create(path, scratch_pool);

      svn_path_remove_components(url_buf,
                                 svn_path_component_count(relative_path));

      /* Now recreate the root_url. */
      session->repos_root = session->session_url;
      session->repos_root.path =
        (char *)svn_fspath__canonicalize(url_buf->data, session->pool);
      session->repos_root_str =
        svn_urlpath__canonicalize(apr_uri_unparse(session->pool,
                                                  &session->repos_root, 0),
                                  session->pool);
    }

  /* Store the repository UUID in the cache. */
  if (!session->uuid)
    {
      session->uuid = apr_pstrdup(session->pool, uuid);
    }

  return SVN_NO_ERROR;
}