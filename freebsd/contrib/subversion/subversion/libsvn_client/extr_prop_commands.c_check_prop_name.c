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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_PROPERTY_NAME ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error_if_wcprop_name (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_prop_is_known_svn_rev_prop (char const*) ; 
 int /*<<< orphan*/  svn_prop_name_is_valid (char const*) ; 

__attribute__((used)) static svn_error_t *
check_prop_name(const char *propname,
                const svn_string_t *propval)
{
  if (svn_prop_is_known_svn_rev_prop(propname))
    return svn_error_createf(SVN_ERR_CLIENT_PROPERTY_NAME, NULL,
                             _("Revision property '%s' not allowed "
                               "in this context"), propname);

  SVN_ERR(error_if_wcprop_name(propname));

  if (propval && ! svn_prop_name_is_valid(propname))
    return svn_error_createf(SVN_ERR_CLIENT_PROPERTY_NAME, NULL,
                             _("Bad property name: '%s'"), propname);

  return SVN_NO_ERROR;
}