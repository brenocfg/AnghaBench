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
struct cesa_softc {int /*<<< orphan*/  sc_dev; } ;
struct cesa_sa_hdesc {int /*<<< orphan*/  cshd_mac_iv_out; int /*<<< orphan*/  cshd_mac_iv_in; int /*<<< orphan*/  cshd_mac_total_dlen; int /*<<< orphan*/  cshd_mac_dlen; int /*<<< orphan*/  cshd_mac_dst; int /*<<< orphan*/  cshd_mac_src; int /*<<< orphan*/  cshd_enc_iv_buf; int /*<<< orphan*/  cshd_enc_iv; int /*<<< orphan*/  cshd_enc_key; int /*<<< orphan*/  cshd_enc_dlen; int /*<<< orphan*/  cshd_enc_dst; int /*<<< orphan*/  cshd_enc_src; int /*<<< orphan*/  cshd_config; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
cesa_dump_cshd(struct cesa_softc *sc, struct cesa_sa_hdesc *cshd)
{
#ifdef DEBUG
	device_t dev;

	dev = sc->sc_dev;
	device_printf(dev, "CESA SA Hardware Descriptor:\n");
	device_printf(dev, "\t\tconfig: 0x%08X\n", cshd->cshd_config);
	device_printf(dev, "\t\te_src:  0x%08X\n", cshd->cshd_enc_src);
	device_printf(dev, "\t\te_dst:  0x%08X\n", cshd->cshd_enc_dst);
	device_printf(dev, "\t\te_dlen: 0x%08X\n", cshd->cshd_enc_dlen);
	device_printf(dev, "\t\te_key:  0x%08X\n", cshd->cshd_enc_key);
	device_printf(dev, "\t\te_iv_1: 0x%08X\n", cshd->cshd_enc_iv);
	device_printf(dev, "\t\te_iv_2: 0x%08X\n", cshd->cshd_enc_iv_buf);
	device_printf(dev, "\t\tm_src:  0x%08X\n", cshd->cshd_mac_src);
	device_printf(dev, "\t\tm_dst:  0x%08X\n", cshd->cshd_mac_dst);
	device_printf(dev, "\t\tm_dlen: 0x%08X\n", cshd->cshd_mac_dlen);
	device_printf(dev, "\t\tm_tlen: 0x%08X\n", cshd->cshd_mac_total_dlen);
	device_printf(dev, "\t\tm_iv_i: 0x%08X\n", cshd->cshd_mac_iv_in);
	device_printf(dev, "\t\tm_iv_o: 0x%08X\n", cshd->cshd_mac_iv_out);
#endif
}