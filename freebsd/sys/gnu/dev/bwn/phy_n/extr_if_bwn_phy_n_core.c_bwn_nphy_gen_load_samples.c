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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bwn_mac {int /*<<< orphan*/  mac_sc; } ;
struct bwn_c32 {int q; int i; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ERRPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BWN_NPHY_BBCFG ; 
 int BWN_NPHY_BBCFG_RSTRX ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 void* CORDIC_CONVERT (int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct bwn_c32 bwn_cordic (int) ; 
 scalar_t__ bwn_is_40mhz (struct bwn_mac*) ; 
 int bwn_nphy_load_samples (struct bwn_mac*,struct bwn_c32*,int) ; 
 int /*<<< orphan*/  free (struct bwn_c32*,int /*<<< orphan*/ ) ; 
 struct bwn_c32* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t bwn_nphy_gen_load_samples(struct bwn_mac *mac, uint32_t freq, uint16_t max,
					bool test)
{
	int i;
	uint16_t bw, len, rot, angle;
	struct bwn_c32 *samples;

	bw = bwn_is_40mhz(mac) ? 40 : 20;
	len = bw << 3;

	if (test) {
		if (BWN_PHY_READ(mac, BWN_NPHY_BBCFG) & BWN_NPHY_BBCFG_RSTRX)
			bw = 82;
		else
			bw = 80;

		if (bwn_is_40mhz(mac))
			bw <<= 1;

		len = bw << 1;
	}

	samples = malloc(len * sizeof(struct bwn_c32), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!samples) {
		BWN_ERRPRINTF(mac->mac_sc, "allocation for samples generation failed\n");
		return 0;
	}
	rot = (((freq * 36) / bw) << 16) / 100;
	angle = 0;

	for (i = 0; i < len; i++) {
		samples[i] = bwn_cordic(angle);
		angle += rot;
		samples[i].q = CORDIC_CONVERT(samples[i].q * max);
		samples[i].i = CORDIC_CONVERT(samples[i].i * max);
	}

	i = bwn_nphy_load_samples(mac, samples, len);
	free(samples, M_DEVBUF);
	return (i < 0) ? 0 : len;
}