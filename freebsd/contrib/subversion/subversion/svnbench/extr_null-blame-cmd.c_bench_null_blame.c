#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_17__ {scalar_t__ number; } ;
struct TYPE_18__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_19__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_20__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
typedef  int svn_boolean_t ;
struct file_rev_baton {int /*<<< orphan*/  byte_count; int /*<<< orphan*/  delta_count; int /*<<< orphan*/  rev_count; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  file_rev_handler ; 
 int /*<<< orphan*/  svn__ui64toa_sep (int /*<<< orphan*/ ,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_revision_number (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__resolve_rev_and_url (TYPE_4__**,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_opt_revision_number ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_get_file_revs2 (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,struct file_rev_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bench_null_blame(const char *target,
                 const svn_opt_revision_t *peg_revision,
                 const svn_opt_revision_t *start,
                 const svn_opt_revision_t *end,
                 svn_boolean_t include_merged_revisions,
                 svn_boolean_t quiet,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *pool)
{
  struct file_rev_baton frb = { 0, 0, 0};
  svn_ra_session_t *ra_session;
  svn_revnum_t start_revnum, end_revnum;
  svn_boolean_t backwards;
  const char *target_abspath_or_url;

  if (start->kind == svn_opt_revision_unspecified
      || end->kind == svn_opt_revision_unspecified)
    return svn_error_create
      (SVN_ERR_CLIENT_BAD_REVISION, NULL, NULL);

  if (svn_path_is_url(target))
    target_abspath_or_url = target;
  else
    SVN_ERR(svn_dirent_get_absolute(&target_abspath_or_url, target, pool));


  /* Get an RA plugin for this filesystem object. */
  SVN_ERR(svn_client__ra_session_from_path2(&ra_session, NULL,
                                            target, NULL, peg_revision,
                                            peg_revision,
                                            ctx, pool));

  SVN_ERR(svn_client__get_revision_number(&start_revnum, NULL, ctx->wc_ctx,
                                          target_abspath_or_url, ra_session,
                                          start, pool));

  SVN_ERR(svn_client__get_revision_number(&end_revnum, NULL, ctx->wc_ctx,
                                          target_abspath_or_url, ra_session,
                                          end, pool));

  {
    svn_client__pathrev_t *loc;
    svn_opt_revision_t younger_end;
    younger_end.kind = svn_opt_revision_number;
    younger_end.value.number = MAX(start_revnum, end_revnum);

    SVN_ERR(svn_client__resolve_rev_and_url(&loc, ra_session,
                                            target, peg_revision,
                                            &younger_end,
                                            ctx, pool));

    /* Make the session point to the real URL. */
    SVN_ERR(svn_ra_reparent(ra_session, loc->url, pool));
  }

  backwards = (start_revnum > end_revnum);

  /* Collect all blame information.
     We need to ensure that we get one revision before the start_rev,
     if available so that we can know what was actually changed in the start
     revision. */
  SVN_ERR(svn_ra_get_file_revs2(ra_session, "",
                                backwards ? start_revnum
                                          : MAX(0, start_revnum-1),
                                end_revnum,
                                include_merged_revisions,
                                file_rev_handler, &frb, pool));

  if (!quiet)
    SVN_ERR(svn_cmdline_printf(pool,
                               _("%15s revisions\n"
                                 "%15s deltas\n"
                                 "%15s bytes in deltas\n"),
                               svn__ui64toa_sep(frb.rev_count, ',', pool),
                               svn__ui64toa_sep(frb.delta_count, ',', pool),
                               svn__ui64toa_sep(frb.byte_count, ',', pool)));

  return SVN_NO_ERROR;
}