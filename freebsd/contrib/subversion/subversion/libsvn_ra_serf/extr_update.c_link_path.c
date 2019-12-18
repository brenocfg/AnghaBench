#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_9__ {char const* update_target; int /*<<< orphan*/  switched_paths; int /*<<< orphan*/  pool; int /*<<< orphan*/  body_template; int /*<<< orphan*/  sess; } ;
typedef  TYPE_2__ report_context_t ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ apr_uri_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ apr_uri_parse (int /*<<< orphan*/ *,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  svn_depth_to_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_ra_serf__get_relative_path (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__report_resource (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_escape_cdata_cstring (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char const*,char*,int /*<<< orphan*/ ,char*,char const*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_protect_pcdata ; 

__attribute__((used)) static svn_error_t *
link_path(void *report_baton,
          const char *path,
          const char *url,
          svn_revnum_t revision,
          svn_depth_t depth,
          svn_boolean_t start_empty,
          const char *lock_token,
          apr_pool_t *pool)
{
  report_context_t *report = report_baton;
  const char *link, *report_target;
  apr_uri_t uri;
  apr_status_t status;
  svn_stringbuf_t *buf = NULL;

  /* We need to pass in the baseline relative path.
   *
   * TODO Confirm that it's on the same server?
   */
  status = apr_uri_parse(pool, url, &uri);
  if (status)
    {
      return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA, NULL,
                               _("Unable to parse URL '%s'"), url);
    }

  SVN_ERR(svn_ra_serf__report_resource(&report_target, report->sess, pool));
  SVN_ERR(svn_ra_serf__get_relative_path(&link, uri.path, report->sess, pool));

  link = apr_pstrcat(pool, "/", link, SVN_VA_NULL);

  svn_xml_make_open_tag(&buf, pool, svn_xml_protect_pcdata, "S:entry",
                        "rev", apr_ltoa(pool, revision),
                        "lock-token", lock_token,
                        "depth", svn_depth_to_word(depth),
                        "linkpath", link,
                        "start-empty", start_empty ? "true" : NULL,
                        SVN_VA_NULL);
  svn_xml_escape_cdata_cstring(&buf, path, pool);
  svn_xml_make_close_tag(&buf, pool, "S:entry");

  SVN_ERR(svn_stream_write(report->body_template, buf->data, &buf->len));

  /* Store the switch roots to allow generating repos_relpaths from just
     the working copy paths. (Needed for HTTPv2) */
  path = apr_pstrdup(report->pool, path);
  link = apr_pstrdup(report->pool, link + 1);
  svn_hash_sets(report->switched_paths, path, link);

  if (!path[0] && report->update_target[0])
    {
      /* The update root is switched. Make sure we store it the way
         we expect it to find */
      svn_hash_sets(report->switched_paths, report->update_target, link);
    }

  return APR_SUCCESS;
}