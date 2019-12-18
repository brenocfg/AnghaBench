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
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CONFIG_FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_TRUE ; 
 int /*<<< orphan*/  svn_config_set (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 

void
svn_config_set_bool(svn_config_t *cfg,
                    const char *section, const char *option,
                    svn_boolean_t value)
{
  svn_config_set(cfg, section, option,
                 (value ? SVN_CONFIG_TRUE : SVN_CONFIG_FALSE));
}