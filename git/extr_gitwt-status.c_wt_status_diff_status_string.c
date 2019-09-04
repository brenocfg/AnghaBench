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
#define  DIFF_STATUS_ADDED 135 
#define  DIFF_STATUS_COPIED 134 
#define  DIFF_STATUS_DELETED 133 
#define  DIFF_STATUS_MODIFIED 132 
#define  DIFF_STATUS_RENAMED 131 
#define  DIFF_STATUS_TYPE_CHANGED 130 
#define  DIFF_STATUS_UNKNOWN 129 
#define  DIFF_STATUS_UNMERGED 128 
 char const* _ (char*) ; 

__attribute__((used)) static const char *wt_status_diff_status_string(int status)
{
	switch (status) {
	case DIFF_STATUS_ADDED:
		return _("new file:");
	case DIFF_STATUS_COPIED:
		return _("copied:");
	case DIFF_STATUS_DELETED:
		return _("deleted:");
	case DIFF_STATUS_MODIFIED:
		return _("modified:");
	case DIFF_STATUS_RENAMED:
		return _("renamed:");
	case DIFF_STATUS_TYPE_CHANGED:
		return _("typechange:");
	case DIFF_STATUS_UNKNOWN:
		return _("unknown:");
	case DIFF_STATUS_UNMERGED:
		return _("unmerged:");
	default:
		return NULL;
	}
}