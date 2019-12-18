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

/* Variables and functions */
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_SERVERS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_category_config (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_get_config(apr_hash_t **cfg_hash,
                      const char *config_dir,
                      apr_pool_t *pool)
{
  svn_config_t *cfg;
  *cfg_hash = svn_hash__make(pool);

  SVN_ERR(get_category_config(&cfg, config_dir, SVN_CONFIG_CATEGORY_SERVERS,
                              pool));
  svn_hash_sets(*cfg_hash, SVN_CONFIG_CATEGORY_SERVERS, cfg);

  SVN_ERR(get_category_config(&cfg, config_dir, SVN_CONFIG_CATEGORY_CONFIG,
                              pool));
  svn_hash_sets(*cfg_hash, SVN_CONFIG_CATEGORY_CONFIG, cfg);

  return SVN_NO_ERROR;
}