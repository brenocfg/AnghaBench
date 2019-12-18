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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_SERVERS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_config_create2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config__get_default_config(apr_hash_t **cfg_hash,
                               apr_pool_t *pool)
{
  svn_config_t *empty_cfg;
  *cfg_hash = svn_hash__make(pool);

  SVN_ERR(svn_config_create2(&empty_cfg, FALSE, FALSE, pool));
  svn_hash_sets(*cfg_hash, SVN_CONFIG_CATEGORY_CONFIG, empty_cfg);

  SVN_ERR(svn_config_create2(&empty_cfg, FALSE, FALSE, pool));
  svn_hash_sets(*cfg_hash, SVN_CONFIG_CATEGORY_SERVERS, empty_cfg);

  return SVN_NO_ERROR;
}