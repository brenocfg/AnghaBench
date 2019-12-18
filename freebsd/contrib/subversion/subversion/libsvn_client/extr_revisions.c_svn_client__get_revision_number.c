#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_15__ {scalar_t__ number; int /*<<< orphan*/  date; } ;
struct TYPE_16__ {int kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
struct TYPE_17__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_RA_ACCESS_REQUIRED ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  svn_opt_revision_base 135 
#define  svn_opt_revision_committed 134 
#define  svn_opt_revision_date 133 
#define  svn_opt_revision_head 132 
#define  svn_opt_revision_number 131 
#define  svn_opt_revision_previous 130 
#define  svn_opt_revision_unspecified 129 
#define  svn_opt_revision_working 128 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 TYPE_3__* svn_ra_get_dated_revision (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_get_latest_revnum (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__node_get_changed_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__node_get_origin (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_revision_number(svn_revnum_t *revnum,
                                svn_revnum_t *youngest_rev,
                                svn_wc_context_t *wc_ctx,
                                const char *local_abspath,
                                svn_ra_session_t *ra_session,
                                const svn_opt_revision_t *revision,
                                apr_pool_t *scratch_pool)
{
  switch (revision->kind)
    {
    case svn_opt_revision_unspecified:
      *revnum = SVN_INVALID_REVNUM;
      break;

    case svn_opt_revision_number:
      *revnum = revision->value.number;
      break;

    case svn_opt_revision_head:
      /* If our caller provided a value for HEAD that he wants us to
         use, we'll use it.  Otherwise, we have to query the
         repository (and possible return our fetched value in
         *YOUNGEST_REV, too). */
      if (youngest_rev && SVN_IS_VALID_REVNUM(*youngest_rev))
        {
          *revnum = *youngest_rev;
        }
      else
        {
          if (! ra_session)
            return svn_error_create(SVN_ERR_CLIENT_RA_ACCESS_REQUIRED,
                                    NULL, NULL);
          SVN_ERR(svn_ra_get_latest_revnum(ra_session, revnum, scratch_pool));
          if (youngest_rev)
            *youngest_rev = *revnum;
        }
      break;

    case svn_opt_revision_working:
    case svn_opt_revision_base:
      {
        svn_error_t *err;

        /* Sanity check. */
        if (local_abspath == NULL)
          return svn_error_create(SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED,
                                  NULL, NULL);

        /* The BASE, COMMITTED, and PREV revision keywords do not
           apply to URLs. */
        if (svn_path_is_url(local_abspath))
          return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                                  _("PREV, BASE, or COMMITTED revision "
                                    "keywords are invalid for URL"));

        err = svn_wc__node_get_origin(NULL, revnum, NULL, NULL, NULL, NULL,
                                      NULL,
                                      wc_ctx, local_abspath, TRUE,
                                      scratch_pool, scratch_pool);

        /* Return the same error as older code did (before and at r935091).
           At least svn_client_proplist4 promises SVN_ERR_ENTRY_NOT_FOUND. */
        if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
          {
            svn_error_clear(err);
            return svn_error_createf(SVN_ERR_ENTRY_NOT_FOUND, NULL,
                                     _("'%s' is not under version control"),
                                     svn_dirent_local_style(local_abspath,
                                                            scratch_pool));
          }
        else
          SVN_ERR(err);

        if (! SVN_IS_VALID_REVNUM(*revnum))
          return svn_error_createf(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                                   _("Path '%s' has no committed "
                                     "revision"),
                                   svn_dirent_local_style(local_abspath,
                                                          scratch_pool));
      }
      break;

    case svn_opt_revision_committed:
    case svn_opt_revision_previous:
      {
        /* Sanity check. */
        if (local_abspath == NULL)
          return svn_error_create(SVN_ERR_CLIENT_VERSIONED_PATH_REQUIRED,
                                  NULL, NULL);

        /* The BASE, COMMITTED, and PREV revision keywords do not
           apply to URLs. */
        if (svn_path_is_url(local_abspath))
          return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                                  _("PREV, BASE, or COMMITTED revision "
                                    "keywords are invalid for URL"));

        SVN_ERR(svn_wc__node_get_changed_info(revnum, NULL, NULL,
                                              wc_ctx, local_abspath,
                                              scratch_pool, scratch_pool));
        if (! SVN_IS_VALID_REVNUM(*revnum))
          return svn_error_createf(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                                   _("Path '%s' has no committed "
                                     "revision"),
                                   svn_dirent_local_style(local_abspath,
                                                          scratch_pool));

        if (revision->kind == svn_opt_revision_previous)
          (*revnum)--;
      }
      break;

    case svn_opt_revision_date:
      /* ### When revision->kind == svn_opt_revision_date, is there an
         ### optimization such that we can compare
         ### revision->value->date with the committed-date in the
         ### entries file (or rather, with some range of which
         ### committed-date is one endpoint), and sometimes avoid a
         ### trip over the RA layer?  The only optimizations I can
         ### think of involve examining other entries to build a
         ### timespan across which committed-revision is known to be
         ### the head, but it doesn't seem worth it.  -kff */
      if (! ra_session)
        return svn_error_create(SVN_ERR_CLIENT_RA_ACCESS_REQUIRED, NULL, NULL);
      SVN_ERR(svn_ra_get_dated_revision(ra_session, revnum,
                                        revision->value.date, scratch_pool));
      break;

    default:
      return svn_error_createf(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                               _("Unrecognized revision type requested for "
                                 "'%s'"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }

  /* Final check -- if our caller provided a youngest revision, and
     the number we wound up with (after talking to the server) is younger
     than that revision, we need to stick to our caller's idea of "youngest".
   */
  if (youngest_rev
      && (revision->kind == svn_opt_revision_head
          || revision->kind == svn_opt_revision_date)
      && SVN_IS_VALID_REVNUM(*youngest_rev)
      && SVN_IS_VALID_REVNUM(*revnum)
      && (*revnum > *youngest_rev))
    *revnum = *youngest_rev;

  return SVN_NO_ERROR;
}