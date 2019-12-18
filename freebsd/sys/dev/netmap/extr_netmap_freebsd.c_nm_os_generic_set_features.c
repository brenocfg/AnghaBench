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
struct netmap_generic_adapter {int rxsg; scalar_t__ txqdisc; } ;

/* Variables and functions */

void
nm_os_generic_set_features(struct netmap_generic_adapter *gna)
{

	gna->rxsg = 1; /* Supported through m_copydata. */
	gna->txqdisc = 0; /* Not supported. */
}