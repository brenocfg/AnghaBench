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
typedef  long long uint64_t ;
typedef  long long uint32_t ;
struct bintime {int frac; scalar_t__ sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime (struct bintime*) ; 

__attribute__((used)) static uint64_t
uuid_time(void)
{
	struct bintime bt;
	uint64_t time = 0x01B21DD213814000LL;

	bintime(&bt);
	time += (uint64_t)bt.sec * 10000000LL;
	time += (10000000LL * (uint32_t)(bt.frac >> 32)) >> 32;
	return (time & ((1LL << 60) - 1LL));
}