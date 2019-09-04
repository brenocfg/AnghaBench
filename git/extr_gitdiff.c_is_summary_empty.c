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
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_filepair {int status; TYPE_2__* two; TYPE_1__* one; int /*<<< orphan*/  score; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  DIFF_STATUS_ADDED 131 
#define  DIFF_STATUS_COPIED 130 
#define  DIFF_STATUS_DELETED 129 
#define  DIFF_STATUS_RENAMED 128 

__attribute__((used)) static int is_summary_empty(const struct diff_queue_struct *q)
{
	int i;

	for (i = 0; i < q->nr; i++) {
		const struct diff_filepair *p = q->queue[i];

		switch (p->status) {
		case DIFF_STATUS_DELETED:
		case DIFF_STATUS_ADDED:
		case DIFF_STATUS_COPIED:
		case DIFF_STATUS_RENAMED:
			return 0;
		default:
			if (p->score)
				return 0;
			if (p->one->mode && p->two->mode &&
			    p->one->mode != p->two->mode)
				return 0;
			break;
		}
	}
	return 1;
}