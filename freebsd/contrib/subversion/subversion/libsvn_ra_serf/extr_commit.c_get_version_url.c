#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char const* data; } ;
typedef  TYPE_3__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_10__ {char* path; } ;
struct TYPE_12__ {TYPE_2__ session_url; int /*<<< orphan*/  wc_callback_baton; TYPE_1__* wc_callbacks; } ;
typedef  TYPE_4__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_wc_prop ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_3__ const**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_REQUEST_FAILED ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__WC_CHECKED_IN_URL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_3__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__fetch_dav_prop (char const**,TYPE_4__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__get_stable_url (char const**,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_urlpath__canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_version_url(const char **checked_in_url,
                svn_ra_serf__session_t *session,
                const char *relpath,
                svn_revnum_t base_revision,
                const char *parent_vsn_url,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  const char *root_checkout;

  if (session->wc_callbacks->get_wc_prop)
    {
      const svn_string_t *current_version;

      SVN_ERR(session->wc_callbacks->get_wc_prop(
                session->wc_callback_baton,
                relpath,
                SVN_RA_SERF__WC_CHECKED_IN_URL,
                &current_version, scratch_pool));

      if (current_version)
        {
          *checked_in_url =
            svn_urlpath__canonicalize(current_version->data, result_pool);
          return SVN_NO_ERROR;
        }
    }

  if (parent_vsn_url)
    {
      root_checkout = parent_vsn_url;
    }
  else
    {
      const char *propfind_url;

      if (SVN_IS_VALID_REVNUM(base_revision))
        {
          /* mod_dav_svn can't handle the "Label:" header that
             svn_ra_serf__deliver_props() is going to try to use for
             this lookup, so we'll do things the hard(er) way, by
             looking up the version URL from a resource in the
             baseline collection. */
          SVN_ERR(svn_ra_serf__get_stable_url(&propfind_url,
                                              NULL /* latest_revnum */,
                                              session,
                                              NULL /* url */, base_revision,
                                              scratch_pool, scratch_pool));
        }
      else
        {
          propfind_url = session->session_url.path;
        }

      SVN_ERR(svn_ra_serf__fetch_dav_prop(&root_checkout, session,
                                          propfind_url, base_revision,
                                          "checked-in",
                                          scratch_pool, scratch_pool));
      if (!root_checkout)
        return svn_error_createf(SVN_ERR_RA_DAV_REQUEST_FAILED, NULL,
                                 _("Path '%s' not present"),
                                 session->session_url.path);

      root_checkout = svn_urlpath__canonicalize(root_checkout, scratch_pool);
    }

  *checked_in_url = svn_path_url_add_component2(root_checkout, relpath,
                                                result_pool);

  return SVN_NO_ERROR;
}