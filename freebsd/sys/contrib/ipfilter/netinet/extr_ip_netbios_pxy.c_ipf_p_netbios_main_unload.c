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
struct TYPE_2__ {int /*<<< orphan*/  fr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUTEX_DESTROY (int /*<<< orphan*/ *) ; 
 int netbios_proxy_init ; 
 TYPE_1__ netbiosfr ; 

void
ipf_p_netbios_main_unload()
{
	if (netbios_proxy_init == 1) {
		MUTEX_DESTROY(&netbiosfr.fr_lock);
		netbios_proxy_init = 0;
	}
}