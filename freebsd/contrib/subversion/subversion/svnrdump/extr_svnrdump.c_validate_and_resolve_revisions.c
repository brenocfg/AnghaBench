#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ number; } ;
struct TYPE_10__ {scalar_t__ kind; TYPE_3__ value; } ;
struct TYPE_7__ {scalar_t__ number; } ;
struct TYPE_8__ {scalar_t__ kind; TYPE_1__ value; } ;
struct TYPE_11__ {TYPE_4__ start_revision; TYPE_2__ end_revision; } ;
typedef  TYPE_5__ opt_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_number ; 
 scalar_t__ svn_opt_revision_unspecified ; 

__attribute__((used)) static svn_error_t *
validate_and_resolve_revisions(opt_baton_t *opt_baton,
                               svn_revnum_t latest_revision,
                               apr_pool_t *pool)
{
  svn_revnum_t provided_start_rev = SVN_INVALID_REVNUM;

  /* Ensure that the start revision is something we can handle.  We
     want a number >= 0.  If unspecified, make it a number (r0) --
     anything else is bogus.  */
  if (opt_baton->start_revision.kind == svn_opt_revision_number)
    {
      provided_start_rev = opt_baton->start_revision.value.number;
    }
  else if (opt_baton->start_revision.kind == svn_opt_revision_head)
    {
      opt_baton->start_revision.kind = svn_opt_revision_number;
      opt_baton->start_revision.value.number = latest_revision;
    }
  else if (opt_baton->start_revision.kind == svn_opt_revision_unspecified)
    {
      opt_baton->start_revision.kind = svn_opt_revision_number;
      opt_baton->start_revision.value.number = 0;
    }

  if (opt_baton->start_revision.kind != svn_opt_revision_number)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                              _("Unsupported revision specifier used; use "
                                "only integer values or 'HEAD'"));
    }

  if ((opt_baton->start_revision.value.number < 0) ||
      (opt_baton->start_revision.value.number > latest_revision))
    {
      return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                               _("Revision '%ld' does not exist"),
                               opt_baton->start_revision.value.number);
    }

  /* Ensure that the end revision is something we can handle.  We want
     a number <= the youngest, and > the start revision.  If
     unspecified, make it a number (start_revision + 1 if that was
     specified, the youngest revision in the repository otherwise) --
     anything else is bogus.  */
  if (opt_baton->end_revision.kind == svn_opt_revision_unspecified)
    {
      opt_baton->end_revision.kind = svn_opt_revision_number;
      if (SVN_IS_VALID_REVNUM(provided_start_rev))
        opt_baton->end_revision.value.number = provided_start_rev;
      else
        opt_baton->end_revision.value.number = latest_revision;
    }
  else if (opt_baton->end_revision.kind == svn_opt_revision_head)
    {
      opt_baton->end_revision.kind = svn_opt_revision_number;
      opt_baton->end_revision.value.number = latest_revision;
    }

  if (opt_baton->end_revision.kind != svn_opt_revision_number)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                              _("Unsupported revision specifier used; use "
                                "only integer values or 'HEAD'"));
    }

  if ((opt_baton->end_revision.value.number < 0) ||
      (opt_baton->end_revision.value.number > latest_revision))
    {
      return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                               _("Revision '%ld' does not exist"),
                               opt_baton->end_revision.value.number);
    }

  /* Finally, make sure that the end revision is younger than the
     start revision.  We don't do "backwards" 'round here.  */
  if (opt_baton->end_revision.value.number <
      opt_baton->start_revision.value.number)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                              _("LOWER revision cannot be greater than "
                                "UPPER revision; consider reversing your "
                                "revision range"));
    }
  return SVN_NO_ERROR;
}