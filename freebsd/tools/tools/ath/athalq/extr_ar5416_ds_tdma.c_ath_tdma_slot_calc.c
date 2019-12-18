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
typedef  int /*<<< orphan*/  t ;
struct if_ath_alq_tdma_slot_calc {int /*<<< orphan*/  avg_minus; int /*<<< orphan*/  avg_plus; int /*<<< orphan*/  tsfdelta; int /*<<< orphan*/  next_slot; int /*<<< orphan*/  nexttbtt; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct if_ath_alq_tdma_slot_calc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned long long,unsigned long long,unsigned long long,int,int,int) ; 

__attribute__((used)) static void
ath_tdma_slot_calc(struct if_ath_alq_payload *a)
{
	struct if_ath_alq_tdma_slot_calc t;

	memcpy(&t, &a->payload, sizeof(t));
	printf("[%u] [%llu] SLOTCALC: NEXTTBTT=%llu nextslot=%llu tsfdelta=%d avg (%d/%d)\n",
	    (unsigned int) be32toh(a->hdr.tstamp),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    (unsigned long long) be64toh(t.nexttbtt),
	    (unsigned long long) be64toh(t.next_slot),
	    (int) be32toh(t.tsfdelta),
	    (int) be32toh(t.avg_plus),
	    (int) be32toh(t.avg_minus));
}