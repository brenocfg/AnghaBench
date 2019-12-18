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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_NEEDS_LOCK ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_prop_is_boolean(const char *prop_name)
{
  /* If we end up with more than 3 of these, we should probably put
     them in a table and use bsearch.  With only three, it doesn't
     make any speed difference.  */
  if (strcmp(prop_name, SVN_PROP_EXECUTABLE) == 0
      || strcmp(prop_name, SVN_PROP_NEEDS_LOCK) == 0
      || strcmp(prop_name, SVN_PROP_SPECIAL) == 0)
    return TRUE;
  return FALSE;
}