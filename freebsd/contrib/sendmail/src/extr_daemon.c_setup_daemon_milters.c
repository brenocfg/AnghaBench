#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  d_inputfilters; int /*<<< orphan*/ * d_inputfilterlist; } ;

/* Variables and functions */
 TYPE_1__* Daemons ; 
 int /*<<< orphan*/  MAXFILTERS ; 
 scalar_t__ MD_SMTP ; 
 int NDaemons ; 
 scalar_t__ OpMode ; 
 int /*<<< orphan*/  milter_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
setup_daemon_milters()
{
	int idx;

	if (OpMode == MD_SMTP)
	{
		/* no need to configure the daemons */
		return;
	}

	for (idx = 0; idx < NDaemons; idx++)
	{
		if (Daemons[idx].d_inputfilterlist != NULL)
		{
			milter_config(Daemons[idx].d_inputfilterlist,
				      Daemons[idx].d_inputfilters,
				      MAXFILTERS);
		}
	}
}