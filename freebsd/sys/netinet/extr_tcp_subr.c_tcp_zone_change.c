#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ipi_zone; } ;

/* Variables and functions */
 TYPE_1__ V_tcbinfo ; 
 int /*<<< orphan*/  V_tcpcb_zone ; 
 int /*<<< orphan*/  maxsockets ; 
 int /*<<< orphan*/  tcp_tw_zone_change () ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_zone_change(void *tag)
{

	uma_zone_set_max(V_tcbinfo.ipi_zone, maxsockets);
	uma_zone_set_max(V_tcpcb_zone, maxsockets);
	tcp_tw_zone_change();
}