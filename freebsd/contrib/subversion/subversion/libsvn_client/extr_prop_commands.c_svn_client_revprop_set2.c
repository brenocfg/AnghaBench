#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char const* prop_name; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_PROPERTY_NAME ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_REVISION_AUTHOR_CONTAINS_NEWLINE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_and_set_revprop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ *,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_revision_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_prop_name_is_valid (char const*) ; 
 int /*<<< orphan*/  svn_ra_change_rev_prop2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_2__ const* const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_has_capability (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify_url (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_revprop_deleted ; 
 int /*<<< orphan*/  svn_wc_notify_revprop_set ; 

svn_error_t *
svn_client_revprop_set2(const char *propname,
                        const svn_string_t *propval,
                        const svn_string_t *original_propval,
                        const char *URL,
                        const svn_opt_revision_t *revision,
                        svn_revnum_t *set_rev,
                        svn_boolean_t force,
                        svn_client_ctx_t *ctx,
                        apr_pool_t *pool)
{
  svn_ra_session_t *ra_session;
  svn_boolean_t be_atomic;

  if ((strcmp(propname, SVN_PROP_REVISION_AUTHOR) == 0)
      && propval
      && strchr(propval->data, '\n') != NULL
      && (! force))
    return svn_error_create(SVN_ERR_CLIENT_REVISION_AUTHOR_CONTAINS_NEWLINE,
                            NULL, _("Author name should not contain a newline;"
                                    " value will not be set unless forced"));

  if (propval && ! svn_prop_name_is_valid(propname))
    return svn_error_createf(SVN_ERR_CLIENT_PROPERTY_NAME, NULL,
                             _("Bad property name: '%s'"), propname);

  /* Open an RA session for the URL. */
  SVN_ERR(svn_client_open_ra_session2(&ra_session, URL, NULL,
                                      ctx, pool, pool));

  /* Resolve the revision into something real, and return that to the
     caller as well. */
  SVN_ERR(svn_client__get_revision_number(set_rev, NULL, ctx->wc_ctx, NULL,
                                          ra_session, revision, pool));

  SVN_ERR(svn_ra_has_capability(ra_session, &be_atomic,
                                SVN_RA_CAPABILITY_ATOMIC_REVPROPS, pool));
  if (be_atomic)
    {
      /* Convert ORIGINAL_PROPVAL to an OLD_VALUE_P. */
      const svn_string_t *const *old_value_p;
      const svn_string_t *unset = NULL;

      if (original_propval == NULL)
        old_value_p = NULL;
      else if (original_propval->data == NULL)
        old_value_p = &unset;
      else
        old_value_p = &original_propval;

      /* The actual RA call. */
      SVN_ERR(svn_ra_change_rev_prop2(ra_session, *set_rev, propname,
                                      old_value_p, propval, pool));
    }
  else
    {
      /* The actual RA call. */
      SVN_ERR(check_and_set_revprop(set_rev, ra_session, propname,
                                    original_propval, propval, pool));
    }

  if (ctx->notify_func2)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify_url(URL,
                                             propval == NULL
                                               ? svn_wc_notify_revprop_deleted
                                               : svn_wc_notify_revprop_set,
                                             pool);
      notify->prop_name = propname;
      notify->revision = *set_rev;

      ctx->notify_func2(ctx->notify_baton2, notify, pool);
    }

  return SVN_NO_ERROR;
}