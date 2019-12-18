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
typedef  int /*<<< orphan*/  t ;
struct if_ath_alq_tdma_timer_config {int dummy; } ;
struct if_ath_alq_payload {int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct if_ath_alq_tdma_timer_config*,int /*<<< orphan*/ *,int) ; 

void
ath_tdma_timer_config(struct if_ath_alq_payload *a)
{
	struct if_ath_alq_tdma_timer_config t;

	memcpy(&t, &a->payload, sizeof(t));
}