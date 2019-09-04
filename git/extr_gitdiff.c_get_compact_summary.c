#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct diff_filepair {scalar_t__ status; TYPE_2__* two; TYPE_1__* one; } ;
struct TYPE_4__ {int mode; } ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_ADDED ; 
 scalar_t__ DIFF_STATUS_DELETED ; 
 scalar_t__ S_ISLNK (int) ; 

__attribute__((used)) static char *get_compact_summary(const struct diff_filepair *p, int is_renamed)
{
	if (!is_renamed) {
		if (p->status == DIFF_STATUS_ADDED) {
			if (S_ISLNK(p->two->mode))
				return "new +l";
			else if ((p->two->mode & 0777) == 0755)
				return "new +x";
			else
				return "new";
		} else if (p->status == DIFF_STATUS_DELETED)
			return "gone";
	}
	if (S_ISLNK(p->one->mode) && !S_ISLNK(p->two->mode))
		return "mode -l";
	else if (!S_ISLNK(p->one->mode) && S_ISLNK(p->two->mode))
		return "mode +l";
	else if ((p->one->mode & 0777) == 0644 &&
		 (p->two->mode & 0777) == 0755)
		return "mode +x";
	else if ((p->one->mode & 0777) == 0755 &&
		 (p->two->mode & 0777) == 0644)
		return "mode -x";
	return NULL;
}