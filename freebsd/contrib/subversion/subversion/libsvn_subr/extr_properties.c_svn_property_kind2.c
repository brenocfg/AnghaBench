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
typedef  int /*<<< orphan*/  svn_prop_kind_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_ENTRY_PREFIX ; 
 int /*<<< orphan*/  SIZEOF_WC_PREFIX ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_PREFIX ; 
 int /*<<< orphan*/  SVN_PROP_WC_PREFIX ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_entry_kind ; 
 int /*<<< orphan*/  svn_prop_regular_kind ; 
 int /*<<< orphan*/  svn_prop_wc_kind ; 

svn_prop_kind_t
svn_property_kind2(const char *prop_name)
{

  if (strncmp(prop_name, SVN_PROP_WC_PREFIX, SIZEOF_WC_PREFIX) == 0)
    return svn_prop_wc_kind;

  if (strncmp(prop_name, SVN_PROP_ENTRY_PREFIX, SIZEOF_ENTRY_PREFIX) == 0)
    return svn_prop_entry_kind;

  return svn_prop_regular_kind;
}