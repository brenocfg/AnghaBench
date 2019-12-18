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
struct sc_pcminfo {struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/  dma_size; int /*<<< orphan*/  buf_base; int /*<<< orphan*/  sdma_channel; } ;

/* Variables and functions */
 int READ4 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int SIER_TDMAE ; 
 int /*<<< orphan*/  SSI_SIER ; 
 int /*<<< orphan*/  WRITE4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ssi_stop(struct sc_pcminfo *scp)
{
	struct sc_info *sc;
	int reg;

	sc = scp->sc;

	reg = READ4(sc, SSI_SIER);
	reg &= ~(SIER_TDMAE);
	WRITE4(sc, SSI_SIER, reg);

	sdma_stop(sc->sdma_channel);

	bzero(sc->buf_base, sc->dma_size);

	return (0);
}