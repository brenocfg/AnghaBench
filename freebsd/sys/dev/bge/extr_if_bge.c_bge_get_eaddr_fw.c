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
typedef  int /*<<< orphan*/  uint8_t ;
struct bge_softc {int bge_flags; int /*<<< orphan*/  bge_dev; } ;

/* Variables and functions */
 int BGE_FLAG_EADDR ; 
 int /*<<< orphan*/  OF_getetheraddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bge_get_eaddr_fw(struct bge_softc *sc, uint8_t ether_addr[])
{
#ifdef __sparc64__
	if (sc->bge_flags & BGE_FLAG_EADDR)
		return (1);

	OF_getetheraddr(sc->bge_dev, ether_addr);
	return (0);
#else
	return (1);
#endif
}