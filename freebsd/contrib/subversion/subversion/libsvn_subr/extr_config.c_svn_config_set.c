#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  option_names_case_sensitive; scalar_t__ read_only; } ;
typedef  TYPE_1__ svn_config_t ;
struct TYPE_14__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_2__ cfg_section_t ;
struct TYPE_15__ {int /*<<< orphan*/  hash_key; int /*<<< orphan*/  state; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ cfg_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* find_option (TYPE_1__*,char const*,char const*,TYPE_2__**) ; 
 int /*<<< orphan*/  option_state_needs_expanding ; 
 int /*<<< orphan*/  remove_expansions (TYPE_1__*) ; 
 TYPE_2__* svn_config_addsection (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  svn_config_create_option (TYPE_3__**,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

void
svn_config_set(svn_config_t *cfg,
               const char *section, const char *option,
               const char *value)
{
  cfg_section_t *sec;
  cfg_option_t *opt;

  /* Ignore write attempts to r/o configurations.
   *
   * Since we should never try to modify r/o data, trigger an assertion
   * in debug mode.
   */
#ifdef SVN_DEBUG
  SVN_ERR_ASSERT_NO_RETURN(!cfg->read_only);
#endif
  if (cfg->read_only)
    return;

  remove_expansions(cfg);

  opt = find_option(cfg, section, option, &sec);
  if (opt != NULL)
    {
      /* Replace the option's value. */
      opt->value = apr_pstrdup(cfg->pool, value);
      opt->state = option_state_needs_expanding;
      return;
    }

  /* Create a new option */
  svn_config_create_option(&opt, option, value,
                           cfg->option_names_case_sensitive,
                           cfg->pool);

  if (sec == NULL)
    {
      /* Even the section doesn't exist. Create it. */
      sec = svn_config_addsection(cfg, section);
    }

  svn_hash_sets(sec->options, opt->hash_key, opt);
}