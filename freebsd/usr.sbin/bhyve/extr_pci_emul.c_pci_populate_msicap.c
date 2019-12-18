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
struct msicap {int nextptr; int msgctrl; int /*<<< orphan*/  capid; } ;

/* Variables and functions */
 int PCIM_MSICTRL_64BIT ; 
 int /*<<< orphan*/  PCIY_MSI ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (struct msicap*,int) ; 
 int ffs (int) ; 

void
pci_populate_msicap(struct msicap *msicap, int msgnum, int nextptr)
{
	int mmc;

	/* Number of msi messages must be a power of 2 between 1 and 32 */
	assert((msgnum & (msgnum - 1)) == 0 && msgnum >= 1 && msgnum <= 32);
	mmc = ffs(msgnum) - 1;

	bzero(msicap, sizeof(struct msicap));
	msicap->capid = PCIY_MSI;
	msicap->nextptr = nextptr;
	msicap->msgctrl = PCIM_MSICTRL_64BIT | (mmc << 1);
}