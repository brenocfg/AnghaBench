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
 unsigned long CKSEG1ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebase ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 int /*<<< orphan*/  panic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic_null_cerr ; 

void set_uncached_handler(unsigned long offset, void *addr,
	unsigned long size)
{
	unsigned long uncached_ebase = CKSEG1ADDR(ebase);

	if (!addr)
		panic(panic_null_cerr);

	memcpy((void *)(uncached_ebase + offset), addr, size);
}