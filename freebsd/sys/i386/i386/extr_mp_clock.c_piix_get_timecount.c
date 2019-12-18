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
struct timecounter {int dummy; } ;

/* Variables and functions */
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  piix_timecounter_address ; 

__attribute__((used)) static unsigned
piix_get_timecount(struct timecounter *tc)
{
	unsigned u1, u2, u3;

	u2 = inl(piix_timecounter_address);
	u3 = inl(piix_timecounter_address);
	do {
		u1 = u2;
		u2 = u3;
		u3 = inl(piix_timecounter_address);
	} while (u1 > u2 || u2 > u3);
	return (u2);
}