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
typedef  int svn_wc_operation_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 char const* _ (char*) ; 
#define  svn_wc_operation_merge 131 
#define  svn_wc_operation_none 130 
#define  svn_wc_operation_switch 129 
#define  svn_wc_operation_update 128 

__attribute__((used)) static const char *
operation_str(svn_wc_operation_t operation)
{
  switch (operation)
    {
    case svn_wc_operation_update: return _("upon update");
    case svn_wc_operation_switch: return _("upon switch");
    case svn_wc_operation_merge:  return _("upon merge");
    case svn_wc_operation_none:   return _("upon none");
    }
  SVN_ERR_MALFUNCTION_NO_RETURN();
  return NULL;
}