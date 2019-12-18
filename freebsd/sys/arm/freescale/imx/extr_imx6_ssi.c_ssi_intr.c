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
struct sc_pcminfo {struct sc_chinfo* chan; struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/  dev; } ;
struct sc_chinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ4 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSI_SISR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ssi_intr(void *arg)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sc_info *sc;

	scp = arg;
	sc = scp->sc;
	ch = &scp->chan[0];

	/* We don't use SSI interrupt */
#if 0
	device_printf(sc->dev, "SSI Intr 0x%08x\n",
	    READ4(sc, SSI_SISR));
#endif
}