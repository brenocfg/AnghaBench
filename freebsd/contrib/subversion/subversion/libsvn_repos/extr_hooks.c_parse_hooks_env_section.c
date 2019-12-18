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
struct parse_hooks_env_section_baton {int /*<<< orphan*/  cfg; int /*<<< orphan*/  hooks_env; } ;
struct parse_hooks_env_option_baton {char const* section; int /*<<< orphan*/  hooks_env; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  parse_hooks_env_option ; 
 int /*<<< orphan*/  svn_config_enumerate2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct parse_hooks_env_option_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
parse_hooks_env_section(const char *name, void *baton, apr_pool_t *pool)
{
  struct parse_hooks_env_section_baton *b = baton;
  struct parse_hooks_env_option_baton bo;

  bo.section = name;
  bo.hooks_env = b->hooks_env;

  (void)svn_config_enumerate2(b->cfg, name, parse_hooks_env_option, &bo, pool);

  return TRUE;
}