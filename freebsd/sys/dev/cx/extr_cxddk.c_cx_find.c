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
typedef  scalar_t__ port_t ;

/* Variables and functions */
 int NBRD ; 
 scalar_t__ cx_probe_board (scalar_t__,int,int) ; 
 scalar_t__* porttab ; 

int cx_find (port_t *board_ports)
{
	int i, n;

	for (i=0, n=0; porttab[i] && n<NBRD; i++)
		if (cx_probe_board (porttab[i], -1, -1))
			board_ports[n++] = porttab[i];
	return n;
}