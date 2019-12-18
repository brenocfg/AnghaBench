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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svnadmin_opt_state {int /*<<< orphan*/  end_revision; int /*<<< orphan*/  start_revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  optrev_to_revnum (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_load_range(svn_revnum_t *lower,
               svn_revnum_t *upper,
               struct svnadmin_opt_state *opt_state)
{
  /* Find the revision numbers at which to start and end.  We only
     support a limited set of revision kinds: number and unspecified. */
  SVN_ERR(optrev_to_revnum(lower, &opt_state->start_revision));
  SVN_ERR(optrev_to_revnum(upper, &opt_state->end_revision));

  /* Fill in implied revisions if necessary. */
  if ((*upper == SVN_INVALID_REVNUM) && (*lower != SVN_INVALID_REVNUM))
    {
      *upper = *lower;
    }
  else if ((*upper != SVN_INVALID_REVNUM) && (*lower == SVN_INVALID_REVNUM))
    {
      *lower = *upper;
    }

  /* Ensure correct range ordering. */
  if (*lower > *upper)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                              _("First revision cannot be higher than second"));
    }

  return SVN_NO_ERROR;
}