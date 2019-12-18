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
typedef  scalar_t__ svn_prop_kind_t ;

/* Variables and functions */
 int SIZEOF_ENTRY_PREFIX ; 
 int SIZEOF_WC_PREFIX ; 
 scalar_t__ svn_prop_entry_kind ; 
 scalar_t__ svn_prop_wc_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 

svn_prop_kind_t
svn_property_kind(int *prefix_len,
                  const char *prop_name)
{
  svn_prop_kind_t kind = svn_property_kind2(prop_name);

  if (prefix_len)
    {
      if (kind == svn_prop_wc_kind)
        *prefix_len = SIZEOF_WC_PREFIX;
      else if (kind == svn_prop_entry_kind)
        *prefix_len = SIZEOF_ENTRY_PREFIX;
      else
        *prefix_len = 0;
    }

  return kind;
}