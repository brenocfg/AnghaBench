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
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  loadav (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loadav_callout ; 

__attribute__((used)) static void
synch_setup(void *dummy)
{
	callout_init(&loadav_callout, 1);

	/* Kick off timeout driven events by calling first time. */
	loadav(NULL);
}