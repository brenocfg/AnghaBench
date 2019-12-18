#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  option_names_case_sensitive; int /*<<< orphan*/  tmp_key; int /*<<< orphan*/  section_names_case_sensitive; int /*<<< orphan*/  sections; } ;
typedef  TYPE_1__ svn_config_t ;
struct TYPE_6__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_2__ cfg_section_t ;
typedef  int /*<<< orphan*/  cfg_option_t ;

/* Variables and functions */
 char* SVN_CONFIG__DEFAULT_SECTION ; 
 scalar_t__ apr_strnatcasecmp (char const*,char*) ; 
 void* get_hash_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cfg_option_t *
find_option(svn_config_t *cfg, const char *section, const char *option,
            cfg_section_t **sectionp)
{
  void *sec_ptr = get_hash_value(cfg->sections, cfg->tmp_key, section,
                                 cfg->section_names_case_sensitive);
  if (sectionp != NULL)
    *sectionp = sec_ptr;

  if (sec_ptr != NULL && option != NULL)
    {
      cfg_section_t *sec = sec_ptr;
      cfg_option_t *opt = get_hash_value(sec->options, cfg->tmp_key, option,
                                         cfg->option_names_case_sensitive);
      /* NOTE: ConfigParser's sections are case sensitive. */
      if (opt == NULL
          && apr_strnatcasecmp(section, SVN_CONFIG__DEFAULT_SECTION) != 0)
        /* Options which aren't found in the requested section are
           also sought after in the default section. */
        opt = find_option(cfg, SVN_CONFIG__DEFAULT_SECTION, option, &sec);
      return opt;
    }

  return NULL;
}