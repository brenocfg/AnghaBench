#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__* childpids ; 
 int maxprocs ; 

__attribute__((used)) static int
findslot(pid_t pid)
{
	int slot;

	for (slot = 0; slot < maxprocs; slot++)
		if (childpids[slot] == pid)
			return (slot);
	return (-1);
}