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
typedef  int /*<<< orphan*/  svn_cmdline_prompt_baton_t ;
typedef  int /*<<< orphan*/  svn_cmdline_prompt_baton2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * prompt (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cmdline_prompt_user2(const char **result,
                         const char *prompt_str,
                         svn_cmdline_prompt_baton_t *baton,
                         apr_pool_t *pool)
{
  /* XXX: We know prompt doesn't use the new members
   * of svn_cmdline_prompt_baton2_t. */
  return prompt(result, prompt_str, FALSE /* don't hide input */,
                (svn_cmdline_prompt_baton2_t *)baton, pool);
}