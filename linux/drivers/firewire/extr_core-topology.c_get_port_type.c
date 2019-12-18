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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static int get_port_type(u32 *sid, int port_index)
{
	int index, shift;

	index = (port_index + 5) / 8;
	shift = 16 - ((port_index + 5) & 7) * 2;
	return (sid[index] >> shift) & 0x03;
}