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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
struct parse_hooks_env_section_baton {int /*<<< orphan*/ * hooks_env; int /*<<< orphan*/ * cfg; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_hooks_env_section ; 
 int /*<<< orphan*/  svn_config_enumerate_sections2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct parse_hooks_env_section_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_read3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 

svn_error_t *
svn_repos__parse_hooks_env(apr_hash_t **hooks_env_p,
                           const char *local_abspath,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  struct parse_hooks_env_section_baton b;
  if (local_abspath)
    {
      svn_node_kind_t kind;
      SVN_ERR(svn_io_check_path(local_abspath, &kind, scratch_pool));

      b.hooks_env = apr_hash_make(result_pool);

      if (kind != svn_node_none)
        {
          svn_config_t *cfg;
          SVN_ERR(svn_config_read3(&cfg, local_abspath, FALSE,
                                  TRUE, TRUE, scratch_pool));
          b.cfg = cfg;

          (void)svn_config_enumerate_sections2(cfg, parse_hooks_env_section,
                                               &b, scratch_pool);
        }

      *hooks_env_p = b.hooks_env;
    }
  else
    {
      *hooks_env_p = NULL;
    }

  return SVN_NO_ERROR;
}