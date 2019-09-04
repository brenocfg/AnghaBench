#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr; } ;
struct wt_status {int status_format; int /*<<< orphan*/  repo; TYPE_1__ ignored; TYPE_3__ untracked; TYPE_2__ change; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  STATUS_FORMAT_LONG 133 
#define  STATUS_FORMAT_NONE 132 
#define  STATUS_FORMAT_PORCELAIN 131 
#define  STATUS_FORMAT_PORCELAIN_V2 130 
#define  STATUS_FORMAT_SHORT 129 
#define  STATUS_FORMAT_UNSPECIFIED 128 
 int /*<<< orphan*/  trace2_data_intmax (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_region_enter (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_region_leave (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wt_longstatus_print (struct wt_status*) ; 
 int /*<<< orphan*/  wt_porcelain_print (struct wt_status*) ; 
 int /*<<< orphan*/  wt_porcelain_v2_print (struct wt_status*) ; 
 int /*<<< orphan*/  wt_shortstatus_print (struct wt_status*) ; 

void wt_status_print(struct wt_status *s)
{
	trace2_data_intmax("status", s->repo, "count/changed", s->change.nr);
	trace2_data_intmax("status", s->repo, "count/untracked",
			   s->untracked.nr);
	trace2_data_intmax("status", s->repo, "count/ignored", s->ignored.nr);

	trace2_region_enter("status", "print", s->repo);

	switch (s->status_format) {
	case STATUS_FORMAT_SHORT:
		wt_shortstatus_print(s);
		break;
	case STATUS_FORMAT_PORCELAIN:
		wt_porcelain_print(s);
		break;
	case STATUS_FORMAT_PORCELAIN_V2:
		wt_porcelain_v2_print(s);
		break;
	case STATUS_FORMAT_UNSPECIFIED:
		BUG("finalize_deferred_config() should have been called");
		break;
	case STATUS_FORMAT_NONE:
	case STATUS_FORMAT_LONG:
		wt_longstatus_print(s);
		break;
	}

	trace2_region_leave("status", "print", s->repo);
}