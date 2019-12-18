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
typedef  scalar_t__ uint64_t ;
struct pt_time_cal {int /*<<< orphan*/  cyc_tsc; int /*<<< orphan*/  cyc_mtc; } ;
struct pt_packet_cyc {scalar_t__ value; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_tcal_update_cyc(struct pt_time_cal *tcal,
		      const struct pt_packet_cyc *packet,
		      const struct pt_config *config)
{
	uint64_t cyc;

	(void) config;

	if (!tcal || !packet)
		return -pte_internal;

	cyc = packet->value;
	tcal->cyc_mtc += cyc;
	tcal->cyc_tsc += cyc;

	return 0;
}