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
struct ifnet {struct an_softc* if_softc; } ;
struct an_softc {unsigned short* an_flash_buffer; int /*<<< orphan*/  mpi350; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_AUX_DATA ; 
 int /*<<< orphan*/  AN_AUX_OFFSET ; 
 int /*<<< orphan*/  AN_AUX_PAGE ; 
 int /*<<< orphan*/  AN_SW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_MEM_AUX_WRITE_4 (struct an_softc*,int,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int) ; 
 int FLASH_SIZE ; 

__attribute__((used)) static int
flashputbuf(struct ifnet *ifp)
{
	unsigned short *bufp;
	int		nwords;
	struct an_softc	*sc = ifp->if_softc;

	/* Write stuff */

	bufp = sc->an_flash_buffer;

	if (!sc->mpi350) {
		CSR_WRITE_2(sc, AN_AUX_PAGE, 0x100);
		CSR_WRITE_2(sc, AN_AUX_OFFSET, 0);

		for (nwords = 0; nwords != FLASH_SIZE / 2; nwords++) {
			CSR_WRITE_2(sc, AN_AUX_DATA, bufp[nwords] & 0xffff);
		}
	} else {
		for (nwords = 0; nwords != FLASH_SIZE / 4; nwords++) {
			CSR_MEM_AUX_WRITE_4(sc, 0x8000,
				((u_int32_t *)bufp)[nwords] & 0xffff);
		}
	}

	CSR_WRITE_2(sc, AN_SW0(sc->mpi350), 0x8000);

	return 0;
}