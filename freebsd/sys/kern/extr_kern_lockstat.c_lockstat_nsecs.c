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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct lock_object {int lo_flags; } ;
struct bintime {int sec; int frac; } ;

/* Variables and functions */
 int LO_NOPROFILE ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 
 int /*<<< orphan*/  lockstat_enabled ; 

uint64_t 
lockstat_nsecs(struct lock_object *lo)
{
	struct bintime bt;
	uint64_t ns;

	if (!lockstat_enabled)
		return (0);
	if ((lo->lo_flags & LO_NOPROFILE) != 0)
		return (0);

	binuptime(&bt);
	ns = bt.sec * (uint64_t)1000000000;
	ns += ((uint64_t)1000000000 * (uint32_t)(bt.frac >> 32)) >> 32;
	return (ns);
}