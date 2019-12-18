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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct adapter {int rx_num_queues; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  rss_key ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MRQC ; 
 int E1000_MRQC_ENABLE_RSS_8Q ; 
 int E1000_MRQC_RSS_FIELD_IPV4 ; 
 int E1000_MRQC_RSS_FIELD_IPV4_TCP ; 
 int E1000_MRQC_RSS_FIELD_IPV4_UDP ; 
 int E1000_MRQC_RSS_FIELD_IPV6 ; 
 int E1000_MRQC_RSS_FIELD_IPV6_TCP ; 
 int E1000_MRQC_RSS_FIELD_IPV6_TCP_EX ; 
 int E1000_MRQC_RSS_FIELD_IPV6_UDP ; 
 int E1000_MRQC_RSS_FIELD_IPV6_UDP_EX ; 
 int /*<<< orphan*/  E1000_RETA (int) ; 
 int /*<<< orphan*/  E1000_RSSRK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  arc4rand (int**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_82575 ; 
 int rss_get_indirection_to_bucket (int) ; 
 int /*<<< orphan*/  rss_getkey (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
igb_initialize_rss_mapping(struct adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	int i;
	int queue_id;
	u32 reta;
	u32 rss_key[10], mrqc, shift = 0;

	/* XXX? */
	if (adapter->hw.mac.type == e1000_82575)
		shift = 6;

	/*
	 * The redirection table controls which destination
	 * queue each bucket redirects traffic to.
	 * Each DWORD represents four queues, with the LSB
	 * being the first queue in the DWORD.
	 *
	 * This just allocates buckets to queues using round-robin
	 * allocation.
	 *
	 * NOTE: It Just Happens to line up with the default
	 * RSS allocation method.
	 */

	/* Warning FM follows */
	reta = 0;
	for (i = 0; i < 128; i++) {
#ifdef RSS
		queue_id = rss_get_indirection_to_bucket(i);
		/*
		 * If we have more queues than buckets, we'll
		 * end up mapping buckets to a subset of the
		 * queues.
		 *
		 * If we have more buckets than queues, we'll
		 * end up instead assigning multiple buckets
		 * to queues.
		 *
		 * Both are suboptimal, but we need to handle
		 * the case so we don't go out of bounds
		 * indexing arrays and such.
		 */
		queue_id = queue_id % adapter->rx_num_queues;
#else
		queue_id = (i % adapter->rx_num_queues);
#endif
		/* Adjust if required */
		queue_id = queue_id << shift;

		/*
		 * The low 8 bits are for hash value (n+0);
		 * The next 8 bits are for hash value (n+1), etc.
		 */
		reta = reta >> 8;
		reta = reta | ( ((uint32_t) queue_id) << 24);
		if ((i & 3) == 3) {
			E1000_WRITE_REG(hw, E1000_RETA(i >> 2), reta);
			reta = 0;
		}
	}

	/* Now fill in hash table */

	/*
	 * MRQC: Multiple Receive Queues Command
	 * Set queuing to RSS control, number depends on the device.
	 */
	mrqc = E1000_MRQC_ENABLE_RSS_8Q;

#ifdef RSS
	/* XXX ew typecasting */
	rss_getkey((uint8_t *) &rss_key);
#else
	arc4rand(&rss_key, sizeof(rss_key), 0);
#endif
	for (i = 0; i < 10; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_RSSRK(0), i, rss_key[i]);

	/*
	 * Configure the RSS fields to hash upon.
	 */
	mrqc |= (E1000_MRQC_RSS_FIELD_IPV4 |
	    E1000_MRQC_RSS_FIELD_IPV4_TCP);
	mrqc |= (E1000_MRQC_RSS_FIELD_IPV6 |
	    E1000_MRQC_RSS_FIELD_IPV6_TCP);
	mrqc |=( E1000_MRQC_RSS_FIELD_IPV4_UDP |
	    E1000_MRQC_RSS_FIELD_IPV6_UDP);
	mrqc |=( E1000_MRQC_RSS_FIELD_IPV6_UDP_EX |
	    E1000_MRQC_RSS_FIELD_IPV6_TCP_EX);

	E1000_WRITE_REG(hw, E1000_MRQC, mrqc);
}