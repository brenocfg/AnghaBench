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
typedef  int u_char ;
typedef  TYPE_1__* hcb_p ;
struct TYPE_4__ {int multiplier; int features; } ;

/* Variables and functions */
 int DBLEN ; 
 int DBLSEL ; 
 int FE_LCKFRQ ; 
 int HSC ; 
 int INB (int /*<<< orphan*/ ) ; 
 int LCKFRQ ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  nc_scntl3 ; 
 int /*<<< orphan*/  nc_stest1 ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  nc_stest4 ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* sym_name (TYPE_1__*) ; 
 int sym_verbose ; 

__attribute__((used)) static void sym_selectclock(hcb_p np, u_char scntl3)
{
	/*
	 *  If multiplier not present or not selected, leave here.
	 */
	if (np->multiplier <= 1) {
		OUTB(nc_scntl3,	scntl3);
		return;
	}

	if (sym_verbose >= 2)
		printf ("%s: enabling clock multiplier\n", sym_name(np));

	OUTB(nc_stest1, DBLEN);	   /* Enable clock multiplier		  */
	/*
	 *  Wait for the LCKFRQ bit to be set if supported by the chip.
	 *  Otherwise wait 20 micro-seconds.
	 */
	if (np->features & FE_LCKFRQ) {
		int i = 20;
		while (!(INB(nc_stest4) & LCKFRQ) && --i > 0)
			UDELAY (20);
		if (!i)
			printf("%s: the chip cannot lock the frequency\n",
				sym_name(np));
	} else
		UDELAY (20);
	OUTB(nc_stest3, HSC);		/* Halt the scsi clock		*/
	OUTB(nc_scntl3,	scntl3);
	OUTB(nc_stest1, (DBLEN|DBLSEL));/* Select clock multiplier	*/
	OUTB(nc_stest3, 0x00);		/* Restart scsi clock 		*/
}