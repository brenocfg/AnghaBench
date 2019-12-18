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
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_TCSR ; 
 int /*<<< orphan*/  READ4 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sai_intr(void *arg)
{
	struct sc_pcminfo *scp;
	struct sc_info *sc;

	scp = arg;
	sc = scp->sc;

	device_printf(sc->dev, "Error I2S_TCSR == 0x%08x\n",
	    READ4(sc, I2S_TCSR));
}