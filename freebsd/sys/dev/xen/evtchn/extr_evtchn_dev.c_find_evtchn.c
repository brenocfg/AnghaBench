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
struct user_evtchn {int /*<<< orphan*/  port; } ;
struct per_user_data {int /*<<< orphan*/  evtchns; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 struct user_evtchn* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct user_evtchn*) ; 
 int /*<<< orphan*/  evtchn_tree ; 

__attribute__((used)) static struct user_evtchn *
find_evtchn(struct per_user_data *u, evtchn_port_t port)
{
	struct user_evtchn tmp = {
		.port = port,
	};

	return (RB_FIND(evtchn_tree, &u->evtchns, &tmp));
}