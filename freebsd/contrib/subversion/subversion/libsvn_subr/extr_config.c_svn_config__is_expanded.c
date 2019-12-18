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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {scalar_t__ state; scalar_t__ value; } ;
typedef  TYPE_1__ cfg_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* find_option (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ option_state_cyclic ; 
 scalar_t__ option_state_expanded ; 
 scalar_t__ strchr (scalar_t__,char) ; 

svn_boolean_t
svn_config__is_expanded(svn_config_t *cfg,
                        const char *section,
                        const char *option)
{
  cfg_option_t *opt;

  if (cfg == NULL)
    return FALSE;

  /* does the option even exist? */
  opt = find_option(cfg, section, option, NULL);
  if (opt == NULL)
    return FALSE;

  /* already expanded? */
  if (   opt->state == option_state_expanded
      || opt->state == option_state_cyclic)
    return TRUE;

  /* needs expansion? */
  if (opt->value && strchr(opt->value, '%'))
    return FALSE;

  /* no expansion necessary */
  return TRUE;
}