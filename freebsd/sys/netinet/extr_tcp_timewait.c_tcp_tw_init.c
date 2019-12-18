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
struct tcptw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,scalar_t__*) ; 
 int /*<<< orphan*/  TW_LOCK_INIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  V_tcptw_zone ; 
 int /*<<< orphan*/  V_tw_lock ; 
 int /*<<< orphan*/  V_twq_2msl ; 
 scalar_t__ maxtcptw ; 
 scalar_t__ tcptw_auto_size () ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,scalar_t__) ; 

void
tcp_tw_init(void)
{

	V_tcptw_zone = uma_zcreate("tcptw", sizeof(struct tcptw),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, 0);
	TUNABLE_INT_FETCH("net.inet.tcp.maxtcptw", &maxtcptw);
	if (maxtcptw == 0)
		uma_zone_set_max(V_tcptw_zone, tcptw_auto_size());
	else
		uma_zone_set_max(V_tcptw_zone, maxtcptw);
	TAILQ_INIT(&V_twq_2msl);
	TW_LOCK_INIT(V_tw_lock, "tcptw");
}