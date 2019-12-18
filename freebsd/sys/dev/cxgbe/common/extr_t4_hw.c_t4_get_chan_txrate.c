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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct adapter {TYPE_1__* chip_params; } ;
struct TYPE_2__ {int nchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_TX_ORATE ; 
 int /*<<< orphan*/  A_TP_TX_TRATE ; 
 int /*<<< orphan*/  G_OFDRATE0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OFDRATE1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OFDRATE2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OFDRATE3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TNLRATE0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TNLRATE1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TNLRATE2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TNLRATE3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_rate (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

void t4_get_chan_txrate(struct adapter *adap, u64 *nic_rate, u64 *ofld_rate)
{
	u32 v;

	v = t4_read_reg(adap, A_TP_TX_TRATE);
	nic_rate[0] = chan_rate(adap, G_TNLRATE0(v));
	nic_rate[1] = chan_rate(adap, G_TNLRATE1(v));
	if (adap->chip_params->nchan > 2) {
		nic_rate[2] = chan_rate(adap, G_TNLRATE2(v));
		nic_rate[3] = chan_rate(adap, G_TNLRATE3(v));
	}

	v = t4_read_reg(adap, A_TP_TX_ORATE);
	ofld_rate[0] = chan_rate(adap, G_OFDRATE0(v));
	ofld_rate[1] = chan_rate(adap, G_OFDRATE1(v));
	if (adap->chip_params->nchan > 2) {
		ofld_rate[2] = chan_rate(adap, G_OFDRATE2(v));
		ofld_rate[3] = chan_rate(adap, G_OFDRATE3(v));
	}
}