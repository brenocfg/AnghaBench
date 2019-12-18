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
struct event_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLEEP_MS (int) ; 
 int callback_count ; 

__attribute__((used)) static void
deferred_callback(struct event_callback *cb, void *arg)
{
	SLEEP_MS(1);
	callback_count += 1;
}