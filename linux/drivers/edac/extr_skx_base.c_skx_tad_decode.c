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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct decoded_addr {scalar_t__ addr; int sktways; int chanways; scalar_t__ chan_addr; int /*<<< orphan*/  channel; int /*<<< orphan*/  imc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKX_GET_TADBASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKX_GET_TADCHNILVOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKX_GET_TADWAYNESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int SKX_MAX_TAD ; 
 scalar_t__ SKX_TAD_BASE (int /*<<< orphan*/ ) ; 
 int SKX_TAD_CHNWAYS (int /*<<< orphan*/ ) ; 
 size_t SKX_TAD_CHN_GRAN (int /*<<< orphan*/ ) ; 
 scalar_t__ SKX_TAD_LIMIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SKX_TAD_OFFSET (int /*<<< orphan*/ ) ; 
 int SKX_TAD_SKTWAYS (int /*<<< orphan*/ ) ; 
 size_t SKX_TAD_SKT_GRAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,scalar_t__,...) ; 
 scalar_t__ skx_do_interleave (scalar_t__,int,int,scalar_t__) ; 
 int* skx_granularity ; 

__attribute__((used)) static bool skx_tad_decode(struct decoded_addr *res)
{
	int i;
	u32 base, wayness, chnilvoffset;
	int skt_interleave_bit, chn_interleave_bit;
	u64 channel_addr;

	for (i = 0; i < SKX_MAX_TAD; i++) {
		SKX_GET_TADBASE(res->dev, res->imc, i, base);
		SKX_GET_TADWAYNESS(res->dev, res->imc, i, wayness);
		if (SKX_TAD_BASE(base) <= res->addr && res->addr <= SKX_TAD_LIMIT(wayness))
			goto tad_found;
	}
	edac_dbg(0, "No TAD entry for 0x%llx\n", res->addr);
	return false;

tad_found:
	res->sktways = SKX_TAD_SKTWAYS(wayness);
	res->chanways = SKX_TAD_CHNWAYS(wayness);
	skt_interleave_bit = skx_granularity[SKX_TAD_SKT_GRAN(base)];
	chn_interleave_bit = skx_granularity[SKX_TAD_CHN_GRAN(base)];

	SKX_GET_TADCHNILVOFFSET(res->dev, res->imc, res->channel, i, chnilvoffset);
	channel_addr = res->addr - SKX_TAD_OFFSET(chnilvoffset);

	if (res->chanways == 3 && skt_interleave_bit > chn_interleave_bit) {
		/* Must handle channel first, then socket */
		channel_addr = skx_do_interleave(channel_addr, chn_interleave_bit,
						 res->chanways, channel_addr);
		channel_addr = skx_do_interleave(channel_addr, skt_interleave_bit,
						 res->sktways, channel_addr);
	} else {
		/* Handle socket then channel. Preserve low bits from original address */
		channel_addr = skx_do_interleave(channel_addr, skt_interleave_bit,
						 res->sktways, res->addr);
		channel_addr = skx_do_interleave(channel_addr, chn_interleave_bit,
						 res->chanways, res->addr);
	}

	res->chan_addr = channel_addr;

	edac_dbg(2, "0x%llx: chan_addr=0x%llx sktways=%d chanways=%d\n",
		 res->addr, res->chan_addr, res->sktways, res->chanways);
	return true;
}