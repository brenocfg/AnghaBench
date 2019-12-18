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
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRST ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  nc_istat ; 

__attribute__((used)) static void sym_chip_reset (hcb_p np)
{
	OUTB (nc_istat, SRST);
	UDELAY (10);
	OUTB (nc_istat, 0);
	UDELAY(2000);	/* For BUS MODE to settle */
}