#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int done; int percent; int size; int now; int elapsed; int start; int eta; } ;
typedef  TYPE_1__ progress_t ;

/* Variables and functions */
 int time (int /*<<< orphan*/ *) ; 

int
progress_update(progress_t *prog, uint64_t done)
{
	prog->done = done;
	prog->percent = (prog->done * 100) / prog->size;
	prog->now = time(NULL);
	prog->elapsed = prog->now - prog->start;
	if (done == 0 || prog->elapsed == 0 || prog->done / prog->elapsed == 0) {
		prog->eta = 0;
	} else {
		prog->eta = prog->size / (prog->done / prog->elapsed) - prog->elapsed;
	}
	return 1;
}