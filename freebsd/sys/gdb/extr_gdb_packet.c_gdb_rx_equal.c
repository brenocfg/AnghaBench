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

/* Variables and functions */
 int gdb_rxp ; 
 int gdb_rxsz ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int,int) ; 

int
gdb_rx_equal(const char *str)
{
	int len;

	len = strlen(str);
	if (len > gdb_rxsz || strncmp(str, gdb_rxp, len) != 0)
		return (0);
	gdb_rxp += len;
	gdb_rxsz -= len;
	return (1);
}