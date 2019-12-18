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

/* Variables and functions */
#define  SVN_WC__WC_NG_VERSION 128 
 char const* _ (char*) ; 

const char *
svn_wc__version_string_from_format(int wc_format)
{
  switch (wc_format)
    {
      case 4: return "<=1.3";
      case 8: return "1.4";
      case 9: return "1.5";
      case 10: return "1.6";
      case SVN_WC__WC_NG_VERSION: return "1.7";
    }
  return _("(unreleased development version)");
}