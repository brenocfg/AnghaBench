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
struct TYPE_3__ {int /*<<< orphan*/  section_names_case_sensitive; int /*<<< orphan*/  tmp_key; int /*<<< orphan*/  sections; } ;
typedef  TYPE_1__ svn_config_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_hash_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_config_has_section(svn_config_t *cfg, const char *section)
{
  return NULL != get_hash_value(cfg->sections, cfg->tmp_key, section,
                                cfg->section_names_case_sensitive);
}