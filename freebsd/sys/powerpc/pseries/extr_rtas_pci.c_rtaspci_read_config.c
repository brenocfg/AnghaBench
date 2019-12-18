#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  phys_mid; int /*<<< orphan*/  phys_hi; } ;
struct rtaspci_softc {int ex_read_pci_config; int /*<<< orphan*/  read_pci_config; TYPE_1__ sc_pcir; scalar_t__ sc_extended_config; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct rtaspci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rtas_call_method (int,int,int,int,int,int*,...) ; 

__attribute__((used)) static uint32_t
rtaspci_read_config(device_t dev, u_int bus, u_int slot, u_int func, u_int reg,
    int width)
{
	struct rtaspci_softc *sc;
	uint32_t retval = 0xffffffff;
	uint32_t config_addr;
	int error, pcierror;

	sc = device_get_softc(dev);
	
	config_addr = ((bus & 0xff) << 16) | ((slot & 0x1f) << 11) |
	    ((func & 0x7) << 8) | (reg & 0xff);
	if (sc->sc_extended_config)
		config_addr |= (reg & 0xf00) << 16;
		
	if (sc->ex_read_pci_config != -1)
		error = rtas_call_method(sc->ex_read_pci_config, 4, 2,
		    config_addr, sc->sc_pcir.phys_hi,
		    sc->sc_pcir.phys_mid, width, &pcierror, &retval);
	else
		error = rtas_call_method(sc->read_pci_config, 2, 2,
		    config_addr, width, &pcierror, &retval);

	/* Sign-extend output */
	switch (width) {
	case 1:
		retval = (int32_t)(int8_t)(retval);
		break;
	case 2:
		retval = (int32_t)(int16_t)(retval);
		break;
	}
	
	if (error < 0 || pcierror != 0)
		retval = 0xffffffff;

	return (retval);
}