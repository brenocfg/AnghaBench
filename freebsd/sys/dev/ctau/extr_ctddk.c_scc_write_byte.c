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
typedef  int /*<<< orphan*/  ct_chan_t ;

/* Variables and functions */
 scalar_t__ scc_write (int /*<<< orphan*/ *,unsigned char*,int) ; 

int scc_write_byte (ct_chan_t *c, unsigned char b)
{
	if (scc_write (c, &b, 1) < 0)
		return -1;
	return b;
}