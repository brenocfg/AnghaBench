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
typedef  int uint32_t ;

/* Variables and functions */
 int UINT_MAX ; 
 int* used_ports_map ; 

__attribute__((used)) static void release_local_port(uint32_t port)
{
	int nr;

	if (port == UINT_MAX)
		return;
	
	nr = port >> 22;
	used_ports_map[nr / 32] &= ~(1 << nr % 32);
}