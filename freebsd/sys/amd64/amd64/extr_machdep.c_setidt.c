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
struct gate_descriptor {uintptr_t gd_looffset; int gd_ist; int gd_type; int gd_dpl; int gd_p; uintptr_t gd_hioffset; scalar_t__ gd_xx; int /*<<< orphan*/  gd_selector; } ;
typedef  int /*<<< orphan*/  inthand_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCODE_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEL_KPL ; 
 struct gate_descriptor* idt ; 

void
setidt(int idx, inthand_t *func, int typ, int dpl, int ist)
{
	struct gate_descriptor *ip;

	ip = idt + idx;
	ip->gd_looffset = (uintptr_t)func;
	ip->gd_selector = GSEL(GCODE_SEL, SEL_KPL);
	ip->gd_ist = ist;
	ip->gd_xx = 0;
	ip->gd_type = typ;
	ip->gd_dpl = dpl;
	ip->gd_p = 1;
	ip->gd_hioffset = ((uintptr_t)func)>>16 ;
}