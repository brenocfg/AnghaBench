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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  option_names_case_sensitive; int /*<<< orphan*/  section_names_case_sensitive; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  for_each_option (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_callback ; 
 int /*<<< orphan*/  svn_config_read3 (TYPE_1__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_config_merge(svn_config_t *cfg, const char *file,
                 svn_boolean_t must_exist)
{
  /* The original config hash shouldn't change if there's an error
     while reading the confguration, so read into a temporary table.
     ### We could use a tmp subpool for this, since merge_cfg is going
     to be tossed afterwards.  Premature optimization, though? */
  svn_config_t *merge_cfg;
  SVN_ERR(svn_config_read3(&merge_cfg, file, must_exist,
                           cfg->section_names_case_sensitive,
                           cfg->option_names_case_sensitive,
                           cfg->pool));

  /* Now copy the new options into the original table. */
  for_each_option(merge_cfg, cfg, merge_cfg->pool, merge_callback);
  return SVN_NO_ERROR;
}