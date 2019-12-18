#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
struct TYPE_4__ {scalar_t__ number; int /*<<< orphan*/  date; } ;
struct TYPE_5__ {scalar_t__ kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ svn_opt_revision_date ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_number ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 int /*<<< orphan*/  svn_repos_dated_revision (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_revnum(svn_revnum_t *revnum, const svn_opt_revision_t *revision,
           svn_revnum_t youngest, svn_repos_t *repos, apr_pool_t *pool)
{
  if (revision->kind == svn_opt_revision_number)
    *revnum = revision->value.number;
  else if (revision->kind == svn_opt_revision_head)
    *revnum = youngest;
  else if (revision->kind == svn_opt_revision_date)
    SVN_ERR(svn_repos_dated_revision(revnum, repos, revision->value.date,
                                     pool));
  else if (revision->kind == svn_opt_revision_unspecified)
    *revnum = SVN_INVALID_REVNUM;
  else
    return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                            _("Invalid revision specifier"));

  if (*revnum > youngest)
    return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
       _("Revisions must not be greater than the youngest revision (%ld)"),
       youngest);

  return SVN_NO_ERROR;
}