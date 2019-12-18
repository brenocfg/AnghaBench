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
struct pt_time {int have_tsc; unsigned long long fc; scalar_t__ lost_cyc; scalar_t__ lost_mtc; scalar_t__ ctc; int /*<<< orphan*/  base; int /*<<< orphan*/  tsc; scalar_t__ have_mtc; scalar_t__ have_tma; } ;
struct pt_packet_tsc {int /*<<< orphan*/  tsc; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_time_update_tsc(struct pt_time *time,
		       const struct pt_packet_tsc *packet,
		       const struct pt_config *config)
{
	(void) config;

	if (!time || !packet)
		return -pte_internal;

	time->have_tsc = 1;
	time->have_tma = 0;
	time->have_mtc = 0;
	time->tsc = time->base = packet->tsc;
	time->ctc = 0;
	time->fc = 0ull;

	/* We got the full time; we recover from previous losses. */
	time->lost_mtc = 0;
	time->lost_cyc = 0;

	return 0;
}