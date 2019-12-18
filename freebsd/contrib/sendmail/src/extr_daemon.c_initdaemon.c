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
struct TYPE_2__ {int d_socket; char* d_name; int /*<<< orphan*/  d_listenqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_LISTENQUEUE ; 
 TYPE_1__* Daemons ; 
 size_t NDaemons ; 

void
initdaemon()
{
	if (NDaemons == 0)
	{
		Daemons[NDaemons].d_socket = -1;
		Daemons[NDaemons].d_listenqueue = DEF_LISTENQUEUE;
		Daemons[NDaemons].d_name = "Daemon0";
		NDaemons = 1;
	}
}