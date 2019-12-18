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
struct TYPE_2__ {int qg_numqueues; } ;

/* Variables and functions */
 int NumQueue ; 
 TYPE_1__** Queue ; 
 int /*<<< orphan*/  SM_TIME_DEFAULT ; 
 scalar_t__ StopRequest ; 
 scalar_t__ print_single_queue (int,int) ; 
 int /*<<< orphan*/  sm_io_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  smioout ; 
 int /*<<< orphan*/  stop_sendmail () ; 

void
printqueue()
{
	int i, k = 0, nrequests = 0;

	for (i = 0; i < NumQueue && Queue[i] != NULL; i++)
	{
		int j;

		k++;
		for (j = 0; j < Queue[i]->qg_numqueues; j++)
		{
			if (StopRequest)
				stop_sendmail();
			nrequests += print_single_queue(i, j);
			k++;
		}
	}
	if (k > 1)
		(void) sm_io_fprintf(smioout, SM_TIME_DEFAULT,
				     "\t\tTotal requests: %d\n",
				     nrequests);
}