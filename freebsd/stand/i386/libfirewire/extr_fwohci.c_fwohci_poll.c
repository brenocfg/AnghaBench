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
typedef  int uint32_t ;
struct fwohci_softc {int dummy; } ;

/* Variables and functions */
 int fwochi_check_stat (struct fwohci_softc*) ; 
 int /*<<< orphan*/  fwohci_intr_body (struct fwohci_softc*,int,int) ; 

void
fwohci_poll(struct fwohci_softc *sc)
{
	uint32_t stat;

	stat = fwochi_check_stat(sc);
	if (stat != 0xffffffff)
		fwohci_intr_body(sc, stat, 1);
}