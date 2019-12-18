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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_string_create (char const*,int /*<<< orphan*/ *) ; 

svn_string_t *
svn_branch__get_default_r0_metadata(apr_pool_t *result_pool)
{
  static const char *default_repos_info
    = "r0: eids 0 1 branches 1\n"
      "B0 root-eid 0 num-eids 1\n"
      "history: parents 0\n"
      "e0: normal -1 .\n";

  return svn_string_create(default_repos_info, result_pool);
}