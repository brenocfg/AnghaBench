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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  t ;
struct if_ath_alq_tdma_beacon_state {int /*<<< orphan*/  beacon_tsf; int /*<<< orphan*/  rx_tsf; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp_usec; int /*<<< orphan*/  tstamp_sec; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct if_ath_alq_tdma_beacon_state*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,unsigned long long,unsigned long long,unsigned long long,scalar_t__) ; 

void
ath_tdma_beacon_state(struct if_ath_alq_payload *a)
{
	struct if_ath_alq_tdma_beacon_state t;
	static uint64_t last_beacon_tx = 0;

	memcpy(&t, &a->payload, sizeof(t));

	printf("[%u.%06u] [%llu] BEACON: RX TSF=%llu Beacon TSF=%llu (%d)\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    (unsigned long long) be64toh(t.rx_tsf),
	    (unsigned long long) be64toh(t.beacon_tsf),
	    be64toh(t.beacon_tsf) - last_beacon_tx);

	last_beacon_tx = be64toh(t.beacon_tsf);
}