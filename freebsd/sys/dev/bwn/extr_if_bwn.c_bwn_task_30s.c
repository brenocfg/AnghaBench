#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int noi_running; scalar_t__ noi_nsamples; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct bwn_mac {TYPE_2__ mac_noise; TYPE_1__ mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_PHYTYPE_G ; 
 int /*<<< orphan*/  bwn_noise_gensample (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_task_30s(struct bwn_mac *mac)
{

	if (mac->mac_phy.type != BWN_PHYTYPE_G || mac->mac_noise.noi_running)
		return;
	mac->mac_noise.noi_running = 1;
	mac->mac_noise.noi_nsamples = 0;

	bwn_noise_gensample(mac);
}