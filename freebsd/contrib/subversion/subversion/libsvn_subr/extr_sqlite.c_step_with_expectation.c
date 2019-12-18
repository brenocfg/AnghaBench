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
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_SQLITE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
step_with_expectation(svn_sqlite__stmt_t* stmt,
                      svn_boolean_t expecting_row)
{
  svn_boolean_t got_row;

  SVN_ERR(svn_sqlite__step(&got_row, stmt));
  if ((got_row && !expecting_row)
      ||
      (!got_row && expecting_row))
    return svn_error_create(SVN_ERR_SQLITE_ERROR,
                            svn_sqlite__reset(stmt),
                            expecting_row
                              ? _("sqlite: Expected database row missing")
                              : _("sqlite: Extra database row found"));

  return SVN_NO_ERROR;
}