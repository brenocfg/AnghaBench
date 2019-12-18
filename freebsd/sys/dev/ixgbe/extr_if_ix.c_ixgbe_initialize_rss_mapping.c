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
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct adapter {int feat_en; int num_rx_queues; int /*<<< orphan*/  iov_mode; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  rss_key ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERETA (int) ; 
 int IXGBE_FEATURE_RSS ; 
 int /*<<< orphan*/  IXGBE_MRQC ; 
 int IXGBE_MRQC_RSSEN ; 
 int IXGBE_MRQC_RSS_FIELD_IPV4 ; 
 int IXGBE_MRQC_RSS_FIELD_IPV4_TCP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV4_UDP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6 ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_EX ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_EX_TCP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_EX_UDP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_TCP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_UDP ; 
 int /*<<< orphan*/  IXGBE_RETA (int) ; 
 int /*<<< orphan*/  IXGBE_RSSRK (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int RSS_HASHTYPE_RSS_IPV4 ; 
 int RSS_HASHTYPE_RSS_IPV6 ; 
 int RSS_HASHTYPE_RSS_IPV6_EX ; 
 int RSS_HASHTYPE_RSS_TCP_IPV4 ; 
 int RSS_HASHTYPE_RSS_TCP_IPV6 ; 
 int RSS_HASHTYPE_RSS_TCP_IPV6_EX ; 
 int RSS_HASHTYPE_RSS_UDP_IPV4 ; 
 int RSS_HASHTYPE_RSS_UDP_IPV6 ; 
 int RSS_HASHTYPE_RSS_UDP_IPV6_EX ; 
 int /*<<< orphan*/  arc4rand (int**,int,int /*<<< orphan*/ ) ; 
 int ixgbe_get_mrqc (int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82598EB 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 
 int rss_get_indirection_to_bucket (int) ; 
 int rss_gethashconfig () ; 
 int /*<<< orphan*/  rss_getkey (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ixgbe_initialize_rss_mapping(struct adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32             reta = 0, mrqc, rss_key[10];
	int             queue_id, table_size, index_mult;
	int             i, j;
	u32             rss_hash_config;

	if (adapter->feat_en & IXGBE_FEATURE_RSS) {
		/* Fetch the configured RSS key */
		rss_getkey((uint8_t *)&rss_key);
	} else {
		/* set up random bits */
		arc4rand(&rss_key, sizeof(rss_key), 0);
	}

	/* Set multiplier for RETA setup and table size based on MAC */
	index_mult = 0x1;
	table_size = 128;
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82598EB:
		index_mult = 0x11;
		break;
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
		table_size = 512;
		break;
	default:
		break;
	}

	/* Set up the redirection table */
	for (i = 0, j = 0; i < table_size; i++, j++) {
		if (j == adapter->num_rx_queues)
			j = 0;

		if (adapter->feat_en & IXGBE_FEATURE_RSS) {
			/*
			 * Fetch the RSS bucket id for the given indirection
			 * entry. Cap it at the number of configured buckets
			 * (which is num_rx_queues.)
			 */
			queue_id = rss_get_indirection_to_bucket(i);
			queue_id = queue_id % adapter->num_rx_queues;
		} else
			queue_id = (j * index_mult);

		/*
		 * The low 8 bits are for hash value (n+0);
		 * The next 8 bits are for hash value (n+1), etc.
		 */
		reta = reta >> 8;
		reta = reta | (((uint32_t)queue_id) << 24);
		if ((i & 3) == 3) {
			if (i < 128)
				IXGBE_WRITE_REG(hw, IXGBE_RETA(i >> 2), reta);
			else
				IXGBE_WRITE_REG(hw, IXGBE_ERETA((i >> 2) - 32),
				    reta);
			reta = 0;
		}
	}

	/* Now fill our hash function seeds */
	for (i = 0; i < 10; i++)
		IXGBE_WRITE_REG(hw, IXGBE_RSSRK(i), rss_key[i]);

	/* Perform hash on these packet types */
	if (adapter->feat_en & IXGBE_FEATURE_RSS)
		rss_hash_config = rss_gethashconfig();
	else {
		/*
		 * Disable UDP - IP fragments aren't currently being handled
		 * and so we end up with a mix of 2-tuple and 4-tuple
		 * traffic.
		 */
		rss_hash_config = RSS_HASHTYPE_RSS_IPV4
		                | RSS_HASHTYPE_RSS_TCP_IPV4
		                | RSS_HASHTYPE_RSS_IPV6
		                | RSS_HASHTYPE_RSS_TCP_IPV6
		                | RSS_HASHTYPE_RSS_IPV6_EX
		                | RSS_HASHTYPE_RSS_TCP_IPV6_EX;
	}

	mrqc = IXGBE_MRQC_RSSEN;
	if (rss_hash_config & RSS_HASHTYPE_RSS_IPV4)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV4;
	if (rss_hash_config & RSS_HASHTYPE_RSS_TCP_IPV4)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV4_TCP;
	if (rss_hash_config & RSS_HASHTYPE_RSS_IPV6)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6;
	if (rss_hash_config & RSS_HASHTYPE_RSS_TCP_IPV6)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6_TCP;
	if (rss_hash_config & RSS_HASHTYPE_RSS_IPV6_EX)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6_EX;
	if (rss_hash_config & RSS_HASHTYPE_RSS_TCP_IPV6_EX)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6_EX_TCP;
	if (rss_hash_config & RSS_HASHTYPE_RSS_UDP_IPV4)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV4_UDP;
	if (rss_hash_config & RSS_HASHTYPE_RSS_UDP_IPV6)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6_UDP;
	if (rss_hash_config & RSS_HASHTYPE_RSS_UDP_IPV6_EX)
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6_EX_UDP;
	mrqc |= ixgbe_get_mrqc(adapter->iov_mode);
	IXGBE_WRITE_REG(hw, IXGBE_MRQC, mrqc);
}