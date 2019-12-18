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
 int /*<<< orphan*/  DLT_IEEE802_11_RADIO ; 
 int open_bpf (char*,int /*<<< orphan*/ ) ; 

int open_rxtx(char *iface, int *rx, int *tx)
{
	*rx = open_bpf(iface, DLT_IEEE802_11_RADIO);
	*tx = *rx;

	return *rx;
}