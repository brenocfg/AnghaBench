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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INC ; 
 int /*<<< orphan*/  DISP_ON ; 
 int EIGHT_BYTE ; 
 int LARGE_FONT ; 
 int ONE_LINE ; 
 int PVC_NLINES ; 
 int SMALL_FONT ; 
 int TWO_LINES ; 
 int /*<<< orphan*/  pvc_clear () ; 
 int /*<<< orphan*/  pvc_dispcnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvc_entrymode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvc_funcset (int) ; 
 int /*<<< orphan*/  pvc_write_string_centered (char*,int) ; 

int pvc_init(void)
{
	u8 cmd = EIGHT_BYTE;

	if (PVC_NLINES == 2)
		cmd |= (SMALL_FONT|TWO_LINES);
	else
		cmd |= (LARGE_FONT|ONE_LINE);
	pvc_funcset(cmd);
	pvc_dispcnt(DISP_ON);
	pvc_entrymode(AUTO_INC);

	pvc_clear();
	pvc_write_string_centered("Display", 0);
	pvc_write_string_centered("Initialized", 1);

	return 0;
}