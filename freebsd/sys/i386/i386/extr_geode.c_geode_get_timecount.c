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
 int /*<<< orphan*/  geode_counter ; 
 int inl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
geode_get_timecount(struct timecounter *tc)
{
	return (inl(geode_counter));
}