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
struct harvest_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RANDOM_RESEED_LOCK () ; 
 int /*<<< orphan*/  RANDOM_RESEED_UNLOCK () ; 

__attribute__((used)) static void
random_other_process_event(struct harvest_event *event)
{

	RANDOM_RESEED_LOCK();
	/*
	 * Do entropy accumulation work here!
	 * You may use this as a chance to unblock the generator.
	 */
	RANDOM_RESEED_UNLOCK();
}