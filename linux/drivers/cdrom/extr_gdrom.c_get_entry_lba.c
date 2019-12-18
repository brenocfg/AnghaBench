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
 int GD_SESSION_OFFSET ; 
 int cpu_to_be32 (int) ; 

__attribute__((used)) static int get_entry_lba(int track)
{
	return (cpu_to_be32(track & 0xffffff00) - GD_SESSION_OFFSET);
}