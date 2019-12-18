#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hcb_p ;
struct TYPE_4__ {int features; int pciclk_khz; } ;

/* Variables and functions */
 int FE_C10 ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK ; 
 int /*<<< orphan*/  nc_stest1 ; 
 scalar_t__ sym_getfreq (TYPE_1__*) ; 

__attribute__((used)) static int sym_getpciclock (hcb_p np)
{
	int f = 0;

	/*
	 *  For the C1010-33, this doesn't work.
	 *  For the C1010-66, this will be tested when I'll have
	 *  such a beast to play with.
	 */
	if (!(np->features & FE_C10)) {
		OUTB (nc_stest1, SCLK);	/* Use the PCI clock as SCSI clock */
		f = (int) sym_getfreq (np);
		OUTB (nc_stest1, 0);
	}
	np->pciclk_khz = f;

	return f;
}