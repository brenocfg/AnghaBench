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
struct TYPE_3__ {int illegal_dport; } ;
union pom_int_ena_w1s {scalar_t__ value; TYPE_1__ s; } ;
struct TYPE_4__ {int se_cores; } ;
struct nitrox_device {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ BIT_ULL (int) ; 
 int /*<<< orphan*/  POM_INT_ENA_W1S ; 
 int /*<<< orphan*/  POM_PERF_CTL ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,scalar_t__) ; 

void nitrox_config_pom_unit(struct nitrox_device *ndev)
{
	union pom_int_ena_w1s pom_int;
	int i;

	/* enable pom interrupts */
	pom_int.value = 0;
	pom_int.s.illegal_dport = 1;
	nitrox_write_csr(ndev, POM_INT_ENA_W1S, pom_int.value);

	/* enable perf counters */
	for (i = 0; i < ndev->hw.se_cores; i++)
		nitrox_write_csr(ndev, POM_PERF_CTL, BIT_ULL(i));
}