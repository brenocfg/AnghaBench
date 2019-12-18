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
struct port_softc {int dummy; } ;
struct port_event {void (* ih ) (void*) ;int pevt; int enabled; void* ih_user; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
#define  DMA_EITHER_EDGE 135 
#define  DMA_FALLING_EDGE 134 
#define  DMA_RISING_EDGE 133 
#define  INT_EITHER_EDGE 132 
#define  INT_FALLING_EDGE 131 
#define  INT_LOGIC_ONE 130 
#define  INT_LOGIC_ZERO 129 
#define  INT_RISING_EDGE 128 
 int PCR_DMA_EE ; 
 int PCR_DMA_FE ; 
 int PCR_DMA_RE ; 
 int PCR_INT_EE ; 
 int PCR_INT_FE ; 
 int PCR_INT_LO ; 
 int PCR_INT_LZ ; 
 int PCR_INT_RE ; 
 int PCR_IRQC_M ; 
 int PCR_IRQC_S ; 
 int /*<<< orphan*/  PORT_PCR (int) ; 
 int READ4 (struct port_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct port_softc*,int /*<<< orphan*/ ,int) ; 
 struct port_event* event_map ; 
 struct port_softc* port_sc ; 

int
port_setup(int pnum, enum ev_type pevt, void (*ih)(void *), void *ih_user)
{
	struct port_event *pev;
	struct port_softc *sc;
	int reg;
	int val;

	sc = port_sc;

	switch (pevt) {
	case DMA_RISING_EDGE:
		val = PCR_DMA_RE;
		break;
	case DMA_FALLING_EDGE:
		val = PCR_DMA_FE;
		break;
	case DMA_EITHER_EDGE:
		val = PCR_DMA_EE;
		break;
	case INT_LOGIC_ZERO:
		val = PCR_INT_LZ;
		break;
	case INT_RISING_EDGE:
		val = PCR_INT_RE;
		break;
	case INT_FALLING_EDGE:
		val = PCR_INT_FE;
		break;
	case INT_EITHER_EDGE:
		val = PCR_INT_EE;
		break;
	case INT_LOGIC_ONE:
		val = PCR_INT_LO;
		break;
	default:
		return (-1);
	}

	reg = READ4(sc, PORT_PCR(pnum));
	reg &= ~(PCR_IRQC_M << PCR_IRQC_S);
	reg |= (val << PCR_IRQC_S);
	WRITE4(sc, PORT_PCR(pnum), reg);

	pev = &event_map[pnum];
	pev->ih = ih;
	pev->ih_user = ih_user;
	pev->pevt = pevt;
	pev->enabled = 1;

	return (0);
}