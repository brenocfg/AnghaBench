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
typedef  scalar_t__ apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_UINT32_MAX ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_cstring_strtoui64 (scalar_t__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

svn_error_t *
svn_cstring_atoui(unsigned int *n, const char *str)
{
  apr_uint64_t val;

  SVN_ERR(svn_cstring_strtoui64(&val, str, 0, APR_UINT32_MAX, 10));
  *n = (unsigned int)val;
  return SVN_NO_ERROR;
}