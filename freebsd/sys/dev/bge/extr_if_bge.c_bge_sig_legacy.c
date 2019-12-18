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
struct bge_softc {scalar_t__ bge_asf_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_FW_DRV_STATE_START ; 
 int /*<<< orphan*/  BGE_FW_DRV_STATE_UNLOAD ; 
#define  BGE_RESET_SHUTDOWN 129 
#define  BGE_RESET_START 128 
 int /*<<< orphan*/  BGE_SRAM_FW_DRV_STATE_MB ; 
 int /*<<< orphan*/  bge_writemem_ind (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_sig_legacy(struct bge_softc *sc, int type)
{

	if (sc->bge_asf_mode) {
		switch (type) {
		case BGE_RESET_START:
			bge_writemem_ind(sc, BGE_SRAM_FW_DRV_STATE_MB,
			    BGE_FW_DRV_STATE_START);
			break;
		case BGE_RESET_SHUTDOWN:
			bge_writemem_ind(sc, BGE_SRAM_FW_DRV_STATE_MB,
			    BGE_FW_DRV_STATE_UNLOAD);
			break;
		}
	}
}