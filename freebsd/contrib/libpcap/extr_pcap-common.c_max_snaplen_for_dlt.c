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
typedef  int u_int ;

/* Variables and functions */
 int DLT_DBUS ; 
 int MAXIMUM_SNAPLEN ; 

u_int
max_snaplen_for_dlt(int dlt)
{
	if (dlt == DLT_DBUS)
		return 134217728;
	else
		return MAXIMUM_SNAPLEN;
}