#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;
struct TYPE_6__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_unspecified ; 

__attribute__((used)) static svn_error_t *
resolve_revnums(svn_revnum_t *start_revnum,
                svn_revnum_t *end_revnum,
                svn_opt_revision_t start_revision,
                svn_opt_revision_t end_revision)
{
  svn_revnum_t start_rev, end_rev;

  /* Special case: neither revision is specified?  This is like
     -r0:HEAD. */
  if ((start_revision.kind == svn_opt_revision_unspecified) &&
      (end_revision.kind == svn_opt_revision_unspecified))
    {
      *start_revnum = 0;
      *end_revnum = SVN_INVALID_REVNUM;
      return SVN_NO_ERROR;
    }

  /* Get the start revision, which must be either HEAD or a number
     (which is required to be a valid one). */
  if (start_revision.kind == svn_opt_revision_head)
    {
      start_rev = SVN_INVALID_REVNUM;
    }
  else
    {
      start_rev = start_revision.value.number;
      if (! SVN_IS_VALID_REVNUM(start_rev))
        return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                 _("Invalid revision number (%ld)"),
                                 start_rev);
    }

  /* Get the end revision, which must be unspecified (meaning,
     "same as the start_rev"), HEAD, or a number (which is
     required to be a valid one). */
  if (end_revision.kind == svn_opt_revision_unspecified)
    {
      end_rev = start_rev;
    }
  else if (end_revision.kind == svn_opt_revision_head)
    {
      end_rev = SVN_INVALID_REVNUM;
    }
  else
    {
      end_rev = end_revision.value.number;
      if (! SVN_IS_VALID_REVNUM(end_rev))
        return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                                 _("Invalid revision number (%ld)"),
                                 end_rev);
    }

  *start_revnum = start_rev;
  *end_revnum = end_rev;
  return SVN_NO_ERROR;
}