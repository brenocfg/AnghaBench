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
typedef  int /*<<< orphan*/  svn_tristate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_bool (scalar_t__*,char const*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_cstring_casecmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_tristate_false ; 
 int /*<<< orphan*/  svn_tristate_true ; 
 int /*<<< orphan*/  svn_tristate_unknown ; 

svn_error_t *
svn_config_get_tristate(svn_config_t *cfg, svn_tristate_t *valuep,
                        const char *section, const char *option,
                        const char *unknown_value,
                        svn_tristate_t default_value)
{
  const char *tmp_value;

  svn_config_get(cfg, &tmp_value, section, option, NULL);

  if (! tmp_value)
    {
      *valuep = default_value;
    }
  else if (0 == svn_cstring_casecmp(tmp_value, unknown_value))
    {
      *valuep = svn_tristate_unknown;
    }
  else
    {
      svn_boolean_t bool_val;
      /* We already incorporated default_value into tmp_value if
         necessary, so the FALSE below will be ignored unless the
         caller is doing something it shouldn't be doing. */
      SVN_ERR(get_bool(&bool_val, tmp_value, FALSE, section, option));
      *valuep = bool_val ? svn_tristate_true : svn_tristate_false;
    }

  return SVN_NO_ERROR;
}