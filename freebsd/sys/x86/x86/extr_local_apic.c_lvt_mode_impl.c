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
typedef  int uint32_t ;
typedef  int u_int ;
struct lvt {scalar_t__ lvt_edgetrigger; scalar_t__ lvt_activehi; int lvt_mode; int lvt_vector; scalar_t__ lvt_masked; } ;
struct lapic {int la_id; } ;

/* Variables and functions */
 int APIC_LVT_DM ; 
#define  APIC_LVT_DM_EXTINT 132 
#define  APIC_LVT_DM_FIXED 131 
#define  APIC_LVT_DM_INIT 130 
#define  APIC_LVT_DM_NMI 129 
#define  APIC_LVT_DM_SMI 128 
 int APIC_LVT_IIPP ; 
 int APIC_LVT_IIPP_INTALO ; 
 int APIC_LVT_M ; 
 int APIC_LVT_TM ; 
 int APIC_LVT_VECTOR ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static uint32_t
lvt_mode_impl(struct lapic *la, struct lvt *lvt, u_int pin, uint32_t value)
{

	value &= ~(APIC_LVT_M | APIC_LVT_TM | APIC_LVT_IIPP | APIC_LVT_DM |
	    APIC_LVT_VECTOR);
	if (lvt->lvt_edgetrigger == 0)
		value |= APIC_LVT_TM;
	if (lvt->lvt_activehi == 0)
		value |= APIC_LVT_IIPP_INTALO;
	if (lvt->lvt_masked)
		value |= APIC_LVT_M;
	value |= lvt->lvt_mode;
	switch (lvt->lvt_mode) {
	case APIC_LVT_DM_NMI:
	case APIC_LVT_DM_SMI:
	case APIC_LVT_DM_INIT:
	case APIC_LVT_DM_EXTINT:
		if (!lvt->lvt_edgetrigger && bootverbose) {
			printf("lapic%u: Forcing LINT%u to edge trigger\n",
			    la->la_id, pin);
			value &= ~APIC_LVT_TM;
		}
		/* Use a vector of 0. */
		break;
	case APIC_LVT_DM_FIXED:
		value |= lvt->lvt_vector;
		break;
	default:
		panic("bad APIC LVT delivery mode: %#x\n", value);
	}
	return (value);
}