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
typedef  int /*<<< orphan*/  uintmax_t ;
struct pccard_function {scalar_t__ pf_mfc_iomax; scalar_t__ pf_mfc_iobase; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCCARD_CCR_IOBASE0 ; 
 int /*<<< orphan*/  PCCARD_CCR_IOBASE1 ; 
 int /*<<< orphan*/  PCCARD_CCR_IOBASE2 ; 
 int /*<<< orphan*/  PCCARD_CCR_IOBASE3 ; 
 int /*<<< orphan*/  PCCARD_CCR_IOSIZE ; 
 int /*<<< orphan*/  pccard_ccr_write (struct pccard_function*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pccard_mfc_adjust_iobase(struct pccard_function *pf, rman_res_t addr,
    rman_res_t offset, rman_res_t size)
{
	bus_size_t iosize, tmp;

	if (addr != 0) {
		if (pf->pf_mfc_iomax == 0) {
			pf->pf_mfc_iobase = addr + offset;
			pf->pf_mfc_iomax = pf->pf_mfc_iobase + size;
		} else {
			/* this makes the assumption that nothing overlaps */
			if (pf->pf_mfc_iobase > addr + offset)
				pf->pf_mfc_iobase = addr + offset;
			if (pf->pf_mfc_iomax < addr + offset + size)
				pf->pf_mfc_iomax = addr + offset + size;
		}
	}

	tmp = pf->pf_mfc_iomax - pf->pf_mfc_iobase;
	/* round up to nearest (2^n)-1 */
	for (iosize = 1; iosize < tmp; iosize <<= 1)
		;
	iosize--;

	DEVPRINTF((pf->dev, "MFC: I/O base %#jx IOSIZE %#jx\n",
	    (uintmax_t)pf->pf_mfc_iobase, (uintmax_t)(iosize + 1)));
	pccard_ccr_write(pf, PCCARD_CCR_IOBASE0,
	    pf->pf_mfc_iobase & 0xff);
	pccard_ccr_write(pf, PCCARD_CCR_IOBASE1,
	    (pf->pf_mfc_iobase >> 8) & 0xff);
	pccard_ccr_write(pf, PCCARD_CCR_IOBASE2, 0);
	pccard_ccr_write(pf, PCCARD_CCR_IOBASE3, 0);
	pccard_ccr_write(pf, PCCARD_CCR_IOSIZE, iosize);
}