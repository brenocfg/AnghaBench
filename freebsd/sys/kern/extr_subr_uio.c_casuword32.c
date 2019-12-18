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
 int casueword32 (int volatile*,int,int*,int) ; 

uint32_t
casuword32(volatile uint32_t *addr, uint32_t old, uint32_t new)
{
	int rv;
	uint32_t val;

	rv = casueword32(addr, old, &val, new);
	return (rv == -1 ? -1 : val);
}