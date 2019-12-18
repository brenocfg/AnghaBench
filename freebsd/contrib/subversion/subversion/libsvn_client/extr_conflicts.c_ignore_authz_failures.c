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
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_AUTHZ_UNREADABLE ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_FORBIDDEN ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_AUTHORIZED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_error_find_cause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ignore_authz_failures(svn_error_t *err)
{
  if (err && (   svn_error_find_cause(err, SVN_ERR_AUTHZ_UNREADABLE)
              || svn_error_find_cause(err, SVN_ERR_RA_NOT_AUTHORIZED)
              || svn_error_find_cause(err, SVN_ERR_RA_DAV_FORBIDDEN)))
    {
      svn_error_clear(err);
      err = SVN_NO_ERROR;
    }

  return err;
}