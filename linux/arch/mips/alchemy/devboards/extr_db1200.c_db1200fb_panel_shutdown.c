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

/* Variables and functions */
 int /*<<< orphan*/  BCSR_BOARD ; 
 int BCSR_BOARD_LCDBL ; 
 int BCSR_BOARD_LCDVDD ; 
 int BCSR_BOARD_LCDVEE ; 
 int /*<<< orphan*/  bcsr_mod (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db1200fb_panel_shutdown(void)
{
	/* Remove power */
	bcsr_mod(BCSR_BOARD, BCSR_BOARD_LCDVEE | BCSR_BOARD_LCDVDD |
			     BCSR_BOARD_LCDBL, 0);
	return 0;
}