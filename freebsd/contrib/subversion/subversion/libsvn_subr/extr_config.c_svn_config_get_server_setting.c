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
typedef  int /*<<< orphan*/  svn_config_t ;

/* Variables and functions */
 char const* SVN_CONFIG_SECTION_GLOBAL ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,char const*,char const*,char const*) ; 

const char*
svn_config_get_server_setting(svn_config_t *cfg,
                              const char* server_group,
                              const char* option_name,
                              const char* default_value)
{
  const char *retval;
  svn_config_get(cfg, &retval, SVN_CONFIG_SECTION_GLOBAL,
                 option_name, default_value);
  if (server_group)
    {
      svn_config_get(cfg, &retval, server_group, option_name, retval);
    }
  return retval;
}