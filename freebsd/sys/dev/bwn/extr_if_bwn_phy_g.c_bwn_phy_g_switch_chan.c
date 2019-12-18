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
typedef  scalar_t__ uint8_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVAR_CC ; 
 int /*<<< orphan*/  BWN_CHANNEL ; 
 int /*<<< orphan*/  BWN_CHANNEL_EXT ; 
 int BWN_HF_JAPAN_CHAN14_OFF ; 
 int BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 scalar_t__ BWN_SPROM1_CC_JP ; 
 scalar_t__ BWN_SPROM1_CC_WORLDWIDE ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int bhnd_nvram_getvar_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 
 int bwn_phy_g_chan2freq (int) ; 
 int /*<<< orphan*/  bwn_spu_workaround (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
bwn_phy_g_switch_chan(struct bwn_mac *mac, int channel, uint8_t spu)
{
	struct bwn_softc	*sc = mac->mac_sc;
	int			 error;

	if (spu != 0)
		bwn_spu_workaround(mac, channel);

	BWN_WRITE_2(mac, BWN_CHANNEL, bwn_phy_g_chan2freq(channel));

	if (channel == 14) {
		uint8_t cc;

		error = bhnd_nvram_getvar_uint8(sc->sc_dev, BHND_NVAR_CC, &cc);
		if (error) {
			device_printf(sc->sc_dev, "error reading country code "
			    "from NVRAM, assuming channel 14 unavailable: %d\n",
			    error);
			cc = BWN_SPROM1_CC_WORLDWIDE;
		}

		if (cc == BWN_SPROM1_CC_JP)
			bwn_hf_write(mac,
			    bwn_hf_read(mac) & ~BWN_HF_JAPAN_CHAN14_OFF);
		else
			bwn_hf_write(mac,
			    bwn_hf_read(mac) | BWN_HF_JAPAN_CHAN14_OFF);
		BWN_WRITE_2(mac, BWN_CHANNEL_EXT,
		    BWN_READ_2(mac, BWN_CHANNEL_EXT) | (1 << 11));
		return;
	}

	BWN_WRITE_2(mac, BWN_CHANNEL_EXT,
	    BWN_READ_2(mac, BWN_CHANNEL_EXT) & 0xf7bf);
}