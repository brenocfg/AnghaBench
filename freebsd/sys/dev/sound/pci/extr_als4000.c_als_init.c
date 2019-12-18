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
typedef  int u_int32_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int ALS_GCR_DMA_EMULATION ; 
 int ALS_GCR_MISC ; 
 int /*<<< orphan*/  ALS_SB16_CONFIG ; 
 int /*<<< orphan*/  ALS_SB16_DMA_SETUP ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 scalar_t__ als_esp_reset (struct sc_info*) ; 
 int als_gcr_rd (struct sc_info*,int) ; 
 int /*<<< orphan*/  als_gcr_wr (struct sc_info*,int,int) ; 
 int als_mix_rd (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  als_mix_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
als_init(struct sc_info *sc)
{
	u_int32_t i, v;

	/* Reset Chip */
	if (als_esp_reset(sc)) {
		return 1;
	}

	/* Enable write on DMA_SETUP register */
	v = als_mix_rd(sc, ALS_SB16_CONFIG);
	als_mix_wr(sc, ALS_SB16_CONFIG, v | 0x80);

	/* Select DMA0 */
	als_mix_wr(sc, ALS_SB16_DMA_SETUP, 0x01);

	/* Disable write on DMA_SETUP register */
	als_mix_wr(sc, ALS_SB16_CONFIG, v & 0x7f);

	/* Enable interrupts */
	v  = als_gcr_rd(sc, ALS_GCR_MISC);
	als_gcr_wr(sc, ALS_GCR_MISC, v | 0x28000);

	/* Black out GCR DMA registers */
	for (i = 0x91; i <= 0x96; i++) {
		als_gcr_wr(sc, i, 0);
	}

	/* Emulation mode */
	v = als_gcr_rd(sc, ALS_GCR_DMA_EMULATION);
	als_gcr_wr(sc, ALS_GCR_DMA_EMULATION, v);
	DEB(printf("GCR_DMA_EMULATION 0x%08x\n", v));
	return 0;
}