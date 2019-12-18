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
typedef  enum svn_wc_status_kind { ____Placeholder_svn_wc_status_kind } svn_wc_status_kind ;

/* Variables and functions */
#define  svn_wc_status_added 140 
#define  svn_wc_status_conflicted 139 
#define  svn_wc_status_deleted 138 
#define  svn_wc_status_external 137 
#define  svn_wc_status_ignored 136 
#define  svn_wc_status_incomplete 135 
#define  svn_wc_status_missing 134 
#define  svn_wc_status_modified 133 
#define  svn_wc_status_none 132 
#define  svn_wc_status_normal 131 
#define  svn_wc_status_obstructed 130 
#define  svn_wc_status_replaced 129 
#define  svn_wc_status_unversioned 128 

__attribute__((used)) static char
generate_status_code(enum svn_wc_status_kind status)
{
  switch (status)
    {
    case svn_wc_status_none:        return ' ';
    case svn_wc_status_normal:      return ' ';
    case svn_wc_status_added:       return 'A';
    case svn_wc_status_missing:     return '!';
    case svn_wc_status_incomplete:  return '!';
    case svn_wc_status_deleted:     return 'D';
    case svn_wc_status_replaced:    return 'R';
    case svn_wc_status_modified:    return 'M';
    case svn_wc_status_conflicted:  return 'C';
    case svn_wc_status_obstructed:  return '~';
    case svn_wc_status_ignored:     return 'I';
    case svn_wc_status_external:    return 'X';
    case svn_wc_status_unversioned: return '?';
    default:                        return '?';
    }
}