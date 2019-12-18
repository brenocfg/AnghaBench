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
struct sec_softc {struct sec_desc* sc_desc; } ;
struct sec_desc {scalar_t__ sd_desc_paddr; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int SEC_CHANNELS ; 
 int /*<<< orphan*/  SEC_LOCK_ASSERT (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  descriptors ; 

__attribute__((used)) static struct sec_desc *
sec_find_desc(struct sec_softc *sc, bus_addr_t paddr)
{
	struct sec_desc *desc = NULL;
	int i;

	SEC_LOCK_ASSERT(sc, descriptors);

	for (i = 0; i < SEC_CHANNELS; i++) {
		if (sc->sc_desc[i].sd_desc_paddr == paddr) {
			desc = &(sc->sc_desc[i]);
			break;
		}
	}

	return (desc);
}