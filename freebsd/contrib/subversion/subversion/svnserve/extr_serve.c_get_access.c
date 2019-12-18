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
typedef  enum access_type { ____Placeholder_access_type } access_type ;

/* Variables and functions */
 int NO_ACCESS ; 
 int READ_ACCESS ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_GENERAL ; 
 int WRITE_ACCESS ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static enum access_type
get_access(svn_config_t *cfg,
           const char *option,
           const char *def,
           svn_boolean_t read_only)
{
  enum access_type result;
  const char *val;

  svn_config_get(cfg, &val, SVN_CONFIG_SECTION_GENERAL, option, def);
  result = (strcmp(val, "write") == 0 ? WRITE_ACCESS :
            strcmp(val, "read") == 0 ? READ_ACCESS : NO_ACCESS);

  return result == WRITE_ACCESS && read_only ? READ_ACCESS : result;
}