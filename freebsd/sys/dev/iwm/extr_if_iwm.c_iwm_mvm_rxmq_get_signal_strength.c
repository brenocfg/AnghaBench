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
struct iwm_softc {int dummy; } ;
struct TYPE_2__ {int energy_a; int energy_b; } ;
struct iwm_rx_mpdu_desc {TYPE_1__ v1; } ;

/* Variables and functions */
 int MAX (int,int) ; 

__attribute__((used)) static int
iwm_mvm_rxmq_get_signal_strength(struct iwm_softc *sc,
    struct iwm_rx_mpdu_desc *desc)
{
	int energy_a, energy_b;

	energy_a = desc->v1.energy_a;
	energy_b = desc->v1.energy_b;
	energy_a = energy_a ? -energy_a : -256;
	energy_b = energy_b ? -energy_b : -256;
	return MAX(energy_a, energy_b);
}