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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_DEFAULT_GLOBAL_IGNORES ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_GLOBAL_IGNORES ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_MISCELLANY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_split_append (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_wc_get_default_ignores(apr_array_header_t **patterns,
                           apr_hash_t *config,
                           apr_pool_t *pool)
{
  svn_config_t *cfg = config
                      ? svn_hash_gets(config, SVN_CONFIG_CATEGORY_CONFIG)
                      : NULL;
  const char *val;

  /* Check the Subversion run-time configuration for global ignores.
     If no configuration value exists, we fall back to our defaults. */
  svn_config_get(cfg, &val, SVN_CONFIG_SECTION_MISCELLANY,
                 SVN_CONFIG_OPTION_GLOBAL_IGNORES,
                 SVN_CONFIG_DEFAULT_GLOBAL_IGNORES);
  *patterns = apr_array_make(pool, 16, sizeof(const char *));

  /* Split the patterns on whitespace, and stuff them into *PATTERNS. */
  svn_cstring_split_append(*patterns, val, "\n\r\t\v ", FALSE, pool);
  return SVN_NO_ERROR;
}