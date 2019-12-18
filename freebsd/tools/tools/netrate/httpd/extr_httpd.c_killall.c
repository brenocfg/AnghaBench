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
struct TYPE_4__ {TYPE_1__* hts; } ;
struct TYPE_3__ {scalar_t__ hts_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int THREADS ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* statep ; 

__attribute__((used)) static void
killall(void)
{
	int i;

	for (i = 0; i < THREADS; i++) {
		if (statep->hts[i].hts_pid != 0)
			(void)kill(statep->hts[i].hts_pid, SIGTERM);
	}
}