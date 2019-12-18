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
typedef  scalar_t__ svn_linenum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_LINENUM_MAX_VALUE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_cstring_strtoui64 (scalar_t__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
parse_offset(svn_linenum_t *offset, const char *number)
{
  svn_error_t *err;
  apr_uint64_t val;

  err = svn_cstring_strtoui64(&val, number, 0, SVN_LINENUM_MAX_VALUE, 10);
  if (err)
    {
      svn_error_clear(err);
      return FALSE;
    }

  *offset = (svn_linenum_t)val;

  return TRUE;
}