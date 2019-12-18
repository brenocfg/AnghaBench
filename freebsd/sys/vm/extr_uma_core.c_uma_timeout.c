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
 int UMA_TIMEOUT ; 
 int /*<<< orphan*/  bucket_enable () ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  uma_callout ; 
 int /*<<< orphan*/  zone_foreach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_timeout ; 

__attribute__((used)) static void
uma_timeout(void *unused)
{
	bucket_enable();
	zone_foreach(zone_timeout);

	/* Reschedule this event */
	callout_reset(&uma_callout, UMA_TIMEOUT * hz, uma_timeout, NULL);
}