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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_FNM_CASE_BLIND ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_fnmatch (char const*,char const*,int) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static svn_boolean_t
match_pattern(const char *pattern, const char *value,
              svn_boolean_t caseblind, apr_pool_t *scratch_pool)
{
  const char *p = apr_psprintf(scratch_pool, "*%s*", pattern);
  int flags = (caseblind ? APR_FNM_CASE_BLIND : 0);

  return (apr_fnmatch(p, value, flags) == APR_SUCCESS);
}