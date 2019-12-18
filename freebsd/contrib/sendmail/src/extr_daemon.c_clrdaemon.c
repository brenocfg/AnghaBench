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
struct TYPE_2__ {int d_socket; } ;

/* Variables and functions */
 TYPE_1__* Daemons ; 
 int NDaemons ; 
 int /*<<< orphan*/  close (int) ; 

void
clrdaemon()
{
	int i;

	for (i = 0; i < NDaemons; i++)
	{
		if (Daemons[i].d_socket >= 0)
			(void) close(Daemons[i].d_socket);
		Daemons[i].d_socket = -1;
	}
}