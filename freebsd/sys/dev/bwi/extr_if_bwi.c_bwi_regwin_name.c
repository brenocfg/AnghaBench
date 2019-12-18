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
struct bwi_regwin {int rw_type; } ;

/* Variables and functions */
#define  BWI_REGWIN_T_BUSPCI 131 
#define  BWI_REGWIN_T_BUSPCIE 130 
#define  BWI_REGWIN_T_COM 129 
#define  BWI_REGWIN_T_MAC 128 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static const char *
bwi_regwin_name(const struct bwi_regwin *rw)
{
	switch (rw->rw_type) {
	case BWI_REGWIN_T_COM:
		return "COM";
	case BWI_REGWIN_T_BUSPCI:
		return "PCI";
	case BWI_REGWIN_T_MAC:
		return "MAC";
	case BWI_REGWIN_T_BUSPCIE:
		return "PCIE";
	}
	panic("unknown regwin type 0x%04x\n", rw->rw_type);
	return NULL;
}