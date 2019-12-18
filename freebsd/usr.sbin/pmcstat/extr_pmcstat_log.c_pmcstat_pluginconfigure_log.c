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
struct TYPE_4__ {size_t pa_plugin; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pl_configure ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 TYPE_2__ args ; 
 int /*<<< orphan*/  atof (char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* plugins ; 
 int /*<<< orphan*/  pmcstat_threshold ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

void
pmcstat_pluginconfigure_log(char *opt)
{

	if (strncmp(opt, "threshold=", 10) == 0) {
		pmcstat_threshold = atof(opt+10);
	} else {
		if (plugins[args.pa_plugin].pl_configure != NULL) {
			if (!plugins[args.pa_plugin].pl_configure(opt))
				err(EX_USAGE,
				    "ERROR: unknown option <%s>.", opt);
		}
	}
}