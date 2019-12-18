#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  option; int /*<<< orphan*/  section; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ svn_cmdline__config_argument_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int ARRAYLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_in_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn__empty_config_sections ; 
 int /*<<< orphan*/ * svn__valid_config_files ; 
 int /*<<< orphan*/ * svn__valid_config_options ; 
 int /*<<< orphan*/ * svn__valid_config_sections ; 

__attribute__((used)) static svn_error_t *
validate_config_option(svn_cmdline__config_argument_t *config_option,
                       apr_pool_t *scratch_pool)
{
  svn_boolean_t arbitrary_keys = FALSE;

  /* TODO: some day, we could also verify that OPTION is valid for SECTION;
     i.e., forbid invalid combinations such as config:auth:diff-extensions. */

#define ARRAYLEN(x) ( sizeof((x)) / sizeof((x)[0]) )

  SVN_ERR(string_in_array(config_option->file, svn__valid_config_files,
                          ARRAYLEN(svn__valid_config_files),
                          scratch_pool));
  SVN_ERR(string_in_array(config_option->section, svn__valid_config_sections,
                          ARRAYLEN(svn__valid_config_sections),
                          scratch_pool));

  /* Don't validate option names for sections such as servers[group],
   * config[tunnels], and config[auto-props] that permit arbitrary options. */
    {
      int i;

      for (i = 0; i < ARRAYLEN(svn__empty_config_sections); i++)
        {
        if (!strcmp(config_option->section, svn__empty_config_sections[i]))
          arbitrary_keys = TRUE;
        }
    }

  if (! arbitrary_keys)
    SVN_ERR(string_in_array(config_option->option, svn__valid_config_options,
                            ARRAYLEN(svn__valid_config_options),
                            scratch_pool));

#undef ARRAYLEN

  return SVN_NO_ERROR;
}