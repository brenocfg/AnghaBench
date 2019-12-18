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
struct user_evtchn {int port; } ;

/* Variables and functions */

__attribute__((used)) static int
evtchn_cmp(struct user_evtchn *u1, struct user_evtchn *u2)
{

	return (u1->port - u2->port);
}