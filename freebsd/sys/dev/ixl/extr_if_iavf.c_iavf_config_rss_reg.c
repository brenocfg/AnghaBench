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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u64 ;
typedef  int u32 ;
struct ixl_vsi {int num_rx_queues; } ;
struct i40e_hw {int dummy; } ;
struct iavf_sc {int /*<<< orphan*/  dev; struct ixl_vsi vsi; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTF (int /*<<< orphan*/ ,char*,int,int) ; 
 int I40E_FILTER_PCTYPE_FRAG_IPV6 ; 
 int I40E_FILTER_PCTYPE_NONF_IPV4_OTHER ; 
 int I40E_FILTER_PCTYPE_NONF_IPV4_TCP ; 
 int I40E_FILTER_PCTYPE_NONF_IPV4_UDP ; 
 int I40E_FILTER_PCTYPE_NONF_IPV6_OTHER ; 
 int I40E_FILTER_PCTYPE_NONF_IPV6_TCP ; 
 int I40E_FILTER_PCTYPE_NONF_IPV6_UDP ; 
 int /*<<< orphan*/  I40E_VFQF_HENA (int) ; 
 int /*<<< orphan*/  I40E_VFQF_HKEY (int) ; 
 int /*<<< orphan*/  I40E_VFQF_HLUT (int) ; 
 int IXL_DEFAULT_RSS_HENA_XL710 ; 
 int IXL_RSS_KEY_SIZE_REG ; 
 int IXL_RSS_VF_LUT_ENTRY_MASK ; 
 int IXL_RSS_VSI_LUT_SIZE ; 
 int RSS_HASHTYPE_RSS_IPV4 ; 
 int RSS_HASHTYPE_RSS_IPV6 ; 
 int RSS_HASHTYPE_RSS_IPV6_EX ; 
 int RSS_HASHTYPE_RSS_TCP_IPV4 ; 
 int RSS_HASHTYPE_RSS_TCP_IPV6 ; 
 int RSS_HASHTYPE_RSS_UDP_IPV4 ; 
 int RSS_HASHTYPE_RSS_UDP_IPV6 ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_get_default_rss_key (int*) ; 
 scalar_t__ rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int rss_get_indirection_to_bucket (int) ; 
 int rss_gethashconfig () ; 
 int /*<<< orphan*/  rss_getkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iavf_config_rss_reg(struct iavf_sc *sc)
{
	struct i40e_hw	*hw = &sc->hw;
	struct ixl_vsi	*vsi = &sc->vsi;
	u32		lut = 0;
	u64		set_hena = 0, hena;
	int		i, j, que_id;
	u32		rss_seed[IXL_RSS_KEY_SIZE_REG];
#ifdef RSS
	u32		rss_hash_config;
#endif
        
	/* Don't set up RSS if using a single queue */
	if (vsi->num_rx_queues == 1) {
		wr32(hw, I40E_VFQF_HENA(0), 0);
		wr32(hw, I40E_VFQF_HENA(1), 0);
		ixl_flush(hw);
		return;
	}

#ifdef RSS
	/* Fetch the configured RSS key */
	rss_getkey((uint8_t *) &rss_seed);
#else
	ixl_get_default_rss_key(rss_seed);
#endif

	/* Fill out hash function seed */
	for (i = 0; i < IXL_RSS_KEY_SIZE_REG; i++)
                wr32(hw, I40E_VFQF_HKEY(i), rss_seed[i]);

	/* Enable PCTYPES for RSS: */
#ifdef RSS
	rss_hash_config = rss_gethashconfig();
	if (rss_hash_config & RSS_HASHTYPE_RSS_IPV4)
                set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_NONF_IPV4_OTHER);
	if (rss_hash_config & RSS_HASHTYPE_RSS_TCP_IPV4)
                set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_NONF_IPV4_TCP);
	if (rss_hash_config & RSS_HASHTYPE_RSS_UDP_IPV4)
                set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_NONF_IPV4_UDP);
	if (rss_hash_config & RSS_HASHTYPE_RSS_IPV6)
                set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_NONF_IPV6_OTHER);
	if (rss_hash_config & RSS_HASHTYPE_RSS_IPV6_EX)
		set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_FRAG_IPV6);
	if (rss_hash_config & RSS_HASHTYPE_RSS_TCP_IPV6)
                set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_NONF_IPV6_TCP);
        if (rss_hash_config & RSS_HASHTYPE_RSS_UDP_IPV6)
                set_hena |= ((u64)1 << I40E_FILTER_PCTYPE_NONF_IPV6_UDP);
#else
	set_hena = IXL_DEFAULT_RSS_HENA_XL710;
#endif
	hena = (u64)rd32(hw, I40E_VFQF_HENA(0)) |
	    ((u64)rd32(hw, I40E_VFQF_HENA(1)) << 32);
	hena |= set_hena;
	wr32(hw, I40E_VFQF_HENA(0), (u32)hena);
	wr32(hw, I40E_VFQF_HENA(1), (u32)(hena >> 32));

	/* Populate the LUT with max no. of queues in round robin fashion */
	for (i = 0, j = 0; i < IXL_RSS_VSI_LUT_SIZE; i++, j++) {
                if (j == vsi->num_rx_queues)
                        j = 0;
#ifdef RSS
		/*
		 * Fetch the RSS bucket id for the given indirection entry.
		 * Cap it at the number of configured buckets (which is
		 * num_rx_queues.)
		 */
		que_id = rss_get_indirection_to_bucket(i);
		que_id = que_id % vsi->num_rx_queues;
#else
		que_id = j;
#endif
                /* lut = 4-byte sliding window of 4 lut entries */
                lut = (lut << 8) | (que_id & IXL_RSS_VF_LUT_ENTRY_MASK);
                /* On i = 3, we have 4 entries in lut; write to the register */
                if ((i & 3) == 3) {
                        wr32(hw, I40E_VFQF_HLUT(i >> 2), lut);
			DDPRINTF(sc->dev, "HLUT(%2d): %#010x", i, lut);
		}
        }
	ixl_flush(hw);
}