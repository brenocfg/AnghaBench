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
typedef  int /*<<< orphan*/  svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_fnmatch (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_utf__xfrm (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
match(const char *pattern, const char *str, svn_membuf_t *buf)
{
  svn_error_t *err;

  err = svn_utf__xfrm(&str, str, strlen(str), TRUE, TRUE, buf);
  if (err)
    {
      /* Can't match invalid data. */
      svn_error_clear(err);
      return FALSE;
    }

  return apr_fnmatch(pattern, str, 0) == APR_SUCCESS;
}