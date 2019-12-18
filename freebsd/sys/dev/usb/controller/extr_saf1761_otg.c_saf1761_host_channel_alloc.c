#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct saf1761_otg_td {scalar_t__ channel; int ep_type; int /*<<< orphan*/  pc; } ;
struct saf1761_otg_softc {int sc_host_intr_map; int* sc_host_intr_busy_map; int sc_host_isoc_map; int* sc_host_isoc_busy_map; int sc_host_async_map; int* sc_host_async_busy_map; } ;
struct TYPE_3__ {scalar_t__ self_suspended; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;

/* Variables and functions */
 TYPE_2__* SAF1761_OTG_PC2UDEV (int /*<<< orphan*/ ) ; 
 scalar_t__ SOTG_HOST_CHANNEL_MAX ; 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int /*<<< orphan*/  ffs (int) ; 

__attribute__((used)) static uint8_t
saf1761_host_channel_alloc(struct saf1761_otg_softc *sc, struct saf1761_otg_td *td)
{
	uint32_t map;
	int x;

	if (td->channel < SOTG_HOST_CHANNEL_MAX)
		return (0);

	/* check if device is suspended */
	if (SAF1761_OTG_PC2UDEV(td->pc)->flags.self_suspended != 0)
		return (1);		/* busy - cannot transfer data */

	switch (td->ep_type) {
	case UE_INTERRUPT:
		map = ~(sc->sc_host_intr_map |
		    sc->sc_host_intr_busy_map[0] |
		    sc->sc_host_intr_busy_map[1]);
		/* find first set bit */
		x = ffs(map) - 1;
		if (x < 0 || x > 31)
			break;
		sc->sc_host_intr_map |= (1U << x);
		td->channel = 32 + x;
		return (0);
	case UE_ISOCHRONOUS:
		map = ~(sc->sc_host_isoc_map |
		    sc->sc_host_isoc_busy_map[0] |
		    sc->sc_host_isoc_busy_map[1]);
		/* find first set bit */
		x = ffs(map) - 1;
		if (x < 0 || x > 31)
			break;
		sc->sc_host_isoc_map |= (1U << x);
		td->channel = x;
		return (0);
	default:
		map = ~(sc->sc_host_async_map |
		    sc->sc_host_async_busy_map[0] |
		    sc->sc_host_async_busy_map[1]);
		/* find first set bit */
		x = ffs(map) - 1;
		if (x < 0 || x > 31)
			break;
		sc->sc_host_async_map |= (1U << x);
		td->channel = 64 + x;
		return (0);
	}
	return (1);
}