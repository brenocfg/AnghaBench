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
typedef  int u_char ;
struct sbni_softc {int dummy; } ;

/* Variables and functions */
 int BU_EMP ; 
 int /*<<< orphan*/  CSR0 ; 
 int ENXIO ; 
 int EN_INT ; 
 int VALID_DECODER ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 

int
sbni_probe(struct sbni_softc *sc)
{
	u_char csr0;

	csr0 = sbni_inb(sc, CSR0);
	if (csr0 != 0xff && csr0 != 0x00) {
		csr0 &= ~EN_INT;
		if (csr0 & BU_EMP)
			csr0 |= EN_INT;
      
		if (VALID_DECODER & (1 << (csr0 >> 4)))
			return (0);
	}
   
	return (ENXIO);
}