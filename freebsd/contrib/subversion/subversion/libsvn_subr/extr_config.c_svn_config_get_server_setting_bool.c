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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_bool (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,char const*) ; 
 char* svn_config_get_server_setting (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_get_server_setting_bool(svn_config_t *cfg,
                                   svn_boolean_t *valuep,
                                   const char *server_group,
                                   const char *option_name,
                                   svn_boolean_t default_value)
{
  const char* tmp_value;
  tmp_value = svn_config_get_server_setting(cfg, server_group,
                                            option_name, NULL);
  return get_bool(valuep, tmp_value, default_value,
                  server_group, option_name);
}