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
typedef  int /*<<< orphan*/  ccb_p ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADDR (int /*<<< orphan*/ ) ; 
 int XE_BAD_PHASE ; 
 int XE_EXTRA_DATA ; 
 int XE_PARITY_ERR ; 
 int XE_SODL_UNRUN ; 
 int XE_SWIDE_OVRUN ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void sym_print_xerr(ccb_p cp, int x_status)
{
	if (x_status & XE_PARITY_ERR) {
		PRINT_ADDR(cp);
		printf ("unrecovered SCSI parity error.\n");
	}
	if (x_status & XE_EXTRA_DATA) {
		PRINT_ADDR(cp);
		printf ("extraneous data discarded.\n");
	}
	if (x_status & XE_BAD_PHASE) {
		PRINT_ADDR(cp);
		printf ("illegal scsi phase (4/5).\n");
	}
	if (x_status & XE_SODL_UNRUN) {
		PRINT_ADDR(cp);
		printf ("ODD transfer in DATA OUT phase.\n");
	}
	if (x_status & XE_SWIDE_OVRUN) {
		PRINT_ADDR(cp);
		printf ("ODD transfer in DATA IN phase.\n");
	}
}