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
 int /*<<< orphan*/  CMPCI_REG_FUNC_1 ; 
 int /*<<< orphan*/  CMPCI_REG_LEGACY_CTRL ; 
 int /*<<< orphan*/  CMPCI_REG_MISC ; 
 int CMPCI_REG_SPDIF0_ENABLE ; 
 int CMPCI_REG_SPDIF_48K ; 
 int CMPCI_REG_W_SPDIF_48L ; 
 int CMPCI_REG_XSPDIF_ENABLE ; 
 int /*<<< orphan*/  cmi_partial_wr4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
cmi_spdif_speed(struct sc_info *sc, int speed) {
	u_int32_t fcr1, lcr, mcr;

	if (speed >= 44100) {
		fcr1 = CMPCI_REG_SPDIF0_ENABLE;
		lcr  = CMPCI_REG_XSPDIF_ENABLE;
		mcr  = (speed == 48000) ?
			CMPCI_REG_W_SPDIF_48L | CMPCI_REG_SPDIF_48K : 0;
	} else {
		fcr1 = mcr = lcr = 0;
	}

	cmi_partial_wr4(sc, CMPCI_REG_MISC, 0,
			CMPCI_REG_W_SPDIF_48L | CMPCI_REG_SPDIF_48K, mcr);
	cmi_partial_wr4(sc, CMPCI_REG_FUNC_1, 0,
			CMPCI_REG_SPDIF0_ENABLE, fcr1);
	cmi_partial_wr4(sc, CMPCI_REG_LEGACY_CTRL, 0,
			CMPCI_REG_XSPDIF_ENABLE, lcr);
}