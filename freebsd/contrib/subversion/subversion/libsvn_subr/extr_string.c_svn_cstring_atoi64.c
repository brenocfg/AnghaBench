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
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_INT64_MAX ; 
 int /*<<< orphan*/  APR_INT64_MIN ; 
 int /*<<< orphan*/  svn_cstring_strtoi64 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_cstring_atoi64(apr_int64_t *n, const char *str)
{
  return svn_error_trace(svn_cstring_strtoi64(n, str, APR_INT64_MIN,
                                              APR_INT64_MAX, 10));
}