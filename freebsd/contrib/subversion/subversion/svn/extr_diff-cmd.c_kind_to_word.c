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
typedef  int svn_client_diff_summarize_kind_t ;

/* Variables and functions */
#define  svn_client_diff_summarize_kind_added 130 
#define  svn_client_diff_summarize_kind_deleted 129 
#define  svn_client_diff_summarize_kind_modified 128 

__attribute__((used)) static const char *
kind_to_word(svn_client_diff_summarize_kind_t kind)
{
  switch (kind)
    {
      case svn_client_diff_summarize_kind_modified: return "modified";
      case svn_client_diff_summarize_kind_added:    return "added";
      case svn_client_diff_summarize_kind_deleted:  return "deleted";
      default:                                      return "none";
    }
}