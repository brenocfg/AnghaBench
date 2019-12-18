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
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  parse_rangelist (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

svn_error_t *
svn_rangelist__parse(svn_rangelist_t **rangelist,
                     const char *str,
                     apr_pool_t *result_pool)
{
  const char *s = str;

  *rangelist = apr_array_make(result_pool, 1, sizeof(svn_merge_range_t *));
  SVN_ERR(parse_rangelist(&s, s + strlen(s), *rangelist, result_pool));
  return SVN_NO_ERROR;
}