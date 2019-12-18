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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_cstring_match_glob_list (char const*,int /*<<< orphan*/  const*) ; 

svn_boolean_t
svn_wc_match_ignore_list(const char *str, const apr_array_header_t *list,
                         apr_pool_t *pool)
{
  /* For now, we simply forward to svn_cstring_match_glob_list. In the
     future, if we support more complex ignore patterns, we would iterate
     over 'list' ourselves, and decide for each pattern how to handle
     it. */

  return svn_cstring_match_glob_list(str, list);
}