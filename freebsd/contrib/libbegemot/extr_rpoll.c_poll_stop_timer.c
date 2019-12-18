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
typedef  size_t u_int ;
struct TYPE_2__ {int /*<<< orphan*/ * func; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  in_dispatch ; 
 int resort ; 
 scalar_t__ rpoll_trace ; 
 int /*<<< orphan*/  stderr ; 
 int* tfd ; 
 size_t tfd_used ; 
 TYPE_1__* tims ; 
 int /*<<< orphan*/  tims_used ; 

void
poll_stop_timer(int handle)
{
	u_int i;

	if(rpoll_trace)
		fprintf(stderr, "poll_stop_timer(%d)", handle);

	tims[handle].func = NULL;
	tims_used--;

	resort = 1;

	if(!in_dispatch)
		return;

	for(i = 0; i < tfd_used; i++)
		if(tfd[i] == handle) {
			tfd[i] = -1;
			break;
		}
}