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
typedef  int svn_cl__prop_use_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_PROP_PREFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
#define  svn_cl__prop_use_edit 130 
#define  svn_cl__prop_use_set 129 
#define  svn_cl__prop_use_use 128 

__attribute__((used)) static const char*
wrong_prop_error_message(svn_cl__prop_use_t prop_use, const char *prop_name,
                         apr_pool_t *scratch_pool)
{
  switch (prop_use)
    {
    case svn_cl__prop_use_set:
      return apr_psprintf(
          scratch_pool,
          _("'%s' is not a valid %s property name; use '--force' to set it"),
          prop_name, SVN_PROP_PREFIX);
    case svn_cl__prop_use_edit:
      return apr_psprintf(
          scratch_pool,
          _("'%s' is not a valid %s property name; use '--force' to edit it"),
          prop_name, SVN_PROP_PREFIX);
    case svn_cl__prop_use_use:
    default:
      return apr_psprintf(
          scratch_pool,
          _("'%s' is not a valid %s property name; use '--force' to use it"),
          prop_name, SVN_PROP_PREFIX);
    }
}