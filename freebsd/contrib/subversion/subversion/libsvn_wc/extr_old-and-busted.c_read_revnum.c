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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_STR_TO_REV (char const*) ; 
 int /*<<< orphan*/  read_val (char const**,char**,char const*) ; 

__attribute__((used)) static svn_error_t *
read_revnum(svn_revnum_t *result,
            char **buf,
            const char *end,
            apr_pool_t *pool)
{
  const char *val;

  SVN_ERR(read_val(&val, buf, end));

  if (val)
    *result = SVN_STR_TO_REV(val);
  else
    *result = SVN_INVALID_REVNUM;

  return SVN_NO_ERROR;
}