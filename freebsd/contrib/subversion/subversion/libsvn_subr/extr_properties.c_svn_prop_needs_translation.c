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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_prop_is_svn_prop (char const*) ; 

svn_boolean_t
svn_prop_needs_translation(const char *propname)
{
  /* ### Someday, we may want to be picky and choosy about which
     properties require UTF8 and EOL conversion.  For now, all "svn:"
     props need it.  */

  return svn_prop_is_svn_prop(propname);
}