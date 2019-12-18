#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ start_rev; scalar_t__ end_rev; int /*<<< orphan*/  source_prop_encoding; int /*<<< orphan*/  quiet; int /*<<< orphan*/  skip_unchanged; int /*<<< orphan*/  config; int /*<<< orphan*/  source_callbacks; int /*<<< orphan*/  from_url; } ;
typedef  TYPE_2__ subcommand_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_STR_TO_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_revprops (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_properties_normalized (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_source_session (int /*<<< orphan*/ **,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
do_copy_revprops(svn_ra_session_t *to_session,
                 subcommand_baton_t *baton, apr_pool_t *pool)
{
  svn_ra_session_t *from_session;
  svn_string_t *last_merged_rev;
  svn_revnum_t i;
  svn_revnum_t step = 1;
  int normalized_rev_props_count = 0;

  SVN_ERR(open_source_session(&from_session, &last_merged_rev,
                              baton->from_url, to_session,
                              &(baton->source_callbacks), baton->config,
                              baton, pool));

  /* An invalid revision means "last-synced" */
  if (! SVN_IS_VALID_REVNUM(baton->start_rev))
    baton->start_rev = SVN_STR_TO_REV(last_merged_rev->data);
  if (! SVN_IS_VALID_REVNUM(baton->end_rev))
    baton->end_rev = SVN_STR_TO_REV(last_merged_rev->data);

  /* Make sure we have revisions within the valid range. */
  if (baton->start_rev > SVN_STR_TO_REV(last_merged_rev->data))
    return svn_error_createf
      (APR_EINVAL, NULL,
       _("Cannot copy revprops for a revision (%ld) that has not "
         "been synchronized yet"), baton->start_rev);
  if (baton->end_rev > SVN_STR_TO_REV(last_merged_rev->data))
    return svn_error_createf
      (APR_EINVAL, NULL,
       _("Cannot copy revprops for a revision (%ld) that has not "
         "been synchronized yet"), baton->end_rev);

  /* Now, copy all the requested revisions, in the requested order. */
  step = (baton->start_rev > baton->end_rev) ? -1 : 1;
  for (i = baton->start_rev; i != baton->end_rev + step; i = i + step)
    {
      int normalized_count;
      SVN_ERR(check_cancel(NULL));
      SVN_ERR(copy_revprops(from_session, to_session, i, TRUE,
                            baton->skip_unchanged, baton->quiet,
                            baton->source_prop_encoding, &normalized_count,
                            pool));
      normalized_rev_props_count += normalized_count;
    }

  /* Notify about normalized props, if any. */
  SVN_ERR(log_properties_normalized(normalized_rev_props_count, 0, pool));

  return SVN_NO_ERROR;
}