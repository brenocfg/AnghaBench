#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_BAD_FILENAME ; 
 int /*<<< orphan*/  SVN_REGISTRY_SYS_CONFIG_PATH ; 
 int /*<<< orphan*/  SVN_REGISTRY_USR_CONFIG_PATH ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* read_all (int /*<<< orphan*/ **,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_config__sys_config_path (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_user_config_path (char const**,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
get_category_config(svn_config_t **cfg,
                    const char *config_dir,
                    const char *category,
                    apr_pool_t *pool)
{
  const char *usr_reg_path = NULL, *sys_reg_path = NULL;
  const char *usr_cfg_path, *sys_cfg_path;
  svn_error_t *err = NULL;

  *cfg = NULL;

  if (! config_dir)
    {
#ifdef WIN32
      sys_reg_path = apr_pstrcat(pool, SVN_REGISTRY_SYS_CONFIG_PATH,
                                 category, SVN_VA_NULL);
      usr_reg_path = apr_pstrcat(pool, SVN_REGISTRY_USR_CONFIG_PATH,
                                 category, SVN_VA_NULL);
#endif /* WIN32 */

      err = svn_config__sys_config_path(&sys_cfg_path, category, pool);
      if ((err) && (err->apr_err == SVN_ERR_BAD_FILENAME))
        {
          sys_cfg_path = NULL;
          svn_error_clear(err);
        }
      else if (err)
        return err;
    }
  else
    sys_cfg_path = NULL;

  SVN_ERR(svn_config_get_user_config_path(&usr_cfg_path, config_dir, category,
                                          pool));
  return read_all(cfg, sys_reg_path, usr_reg_path,
                  sys_cfg_path, usr_cfg_path, pool);
}