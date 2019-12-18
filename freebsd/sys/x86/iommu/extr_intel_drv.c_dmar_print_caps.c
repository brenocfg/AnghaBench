#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct dmar_unit {int hw_cap; int hw_ecap; int /*<<< orphan*/  hw_ver; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Segment; scalar_t__ Address; } ;
typedef  TYPE_1__ ACPI_DMAR_HARDWARE_UNIT ;

/* Variables and functions */
 int DMAR_CAP_FRO (int) ; 
 int DMAR_CAP_MAMV (int) ; 
 int DMAR_CAP_MGAW (int) ; 
 int DMAR_CAP_ND (int) ; 
 int DMAR_CAP_NFR (int) ; 
 int DMAR_CAP_PSI ; 
 int DMAR_CAP_SAGAW (int) ; 
 int DMAR_CAP_SPS (int) ; 
 int DMAR_ECAP_IRO (int) ; 
 int DMAR_ECAP_MHMV (int) ; 
 int /*<<< orphan*/  DMAR_MAJOR_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAR_MINOR_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dmar_print_caps(device_t dev, struct dmar_unit *unit,
    ACPI_DMAR_HARDWARE_UNIT *dmaru)
{
	uint32_t caphi, ecaphi;

	device_printf(dev, "regs@0x%08jx, ver=%d.%d, seg=%d, flags=<%b>\n",
	    (uintmax_t)dmaru->Address, DMAR_MAJOR_VER(unit->hw_ver),
	    DMAR_MINOR_VER(unit->hw_ver), dmaru->Segment,
	    dmaru->Flags, "\020\001INCLUDE_ALL_PCI");
	caphi = unit->hw_cap >> 32;
	device_printf(dev, "cap=%b,", (u_int)unit->hw_cap,
	    "\020\004AFL\005WBF\006PLMR\007PHMR\010CM\027ZLR\030ISOCH");
	printf("%b, ", caphi, "\020\010PSI\027DWD\030DRD\031FL1GP\034PSI");
	printf("ndoms=%d, sagaw=%d, mgaw=%d, fro=%d, nfr=%d, superp=%d",
	    DMAR_CAP_ND(unit->hw_cap), DMAR_CAP_SAGAW(unit->hw_cap),
	    DMAR_CAP_MGAW(unit->hw_cap), DMAR_CAP_FRO(unit->hw_cap),
	    DMAR_CAP_NFR(unit->hw_cap), DMAR_CAP_SPS(unit->hw_cap));
	if ((unit->hw_cap & DMAR_CAP_PSI) != 0)
		printf(", mamv=%d", DMAR_CAP_MAMV(unit->hw_cap));
	printf("\n");
	ecaphi = unit->hw_ecap >> 32;
	device_printf(dev, "ecap=%b,", (u_int)unit->hw_ecap,
	    "\020\001C\002QI\003DI\004IR\005EIM\007PT\010SC\031ECS\032MTS"
	    "\033NEST\034DIS\035PASID\036PRS\037ERS\040SRS");
	printf("%b, ", ecaphi, "\020\002NWFS\003EAFS");
	printf("mhmw=%d, iro=%d\n", DMAR_ECAP_MHMV(unit->hw_ecap),
	    DMAR_ECAP_IRO(unit->hw_ecap));
}