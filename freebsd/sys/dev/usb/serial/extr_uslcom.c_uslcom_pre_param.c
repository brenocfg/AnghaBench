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
typedef  scalar_t__ uint32_t ;
struct uslcom_softc {int sc_partnum; } ;
struct ucom_softc {struct uslcom_softc* sc_parent; } ;
struct termios {scalar_t__ c_ospeed; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USLCOM_PARTNUM_CP2101 132 
#define  USLCOM_PARTNUM_CP2102 131 
#define  USLCOM_PARTNUM_CP2103 130 
#define  USLCOM_PARTNUM_CP2104 129 
#define  USLCOM_PARTNUM_CP2105 128 

__attribute__((used)) static int
uslcom_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uslcom_softc *sc = ucom->sc_parent;
	uint32_t maxspeed;

	switch (sc->sc_partnum) {
	case USLCOM_PARTNUM_CP2104:
	case USLCOM_PARTNUM_CP2105:
		maxspeed = 2000000;
		break;
	case USLCOM_PARTNUM_CP2101:
	case USLCOM_PARTNUM_CP2102:
	case USLCOM_PARTNUM_CP2103:
	default:
		maxspeed = 921600;
		break;
	}
	if (t->c_ospeed <= 0 || t->c_ospeed > maxspeed)
		return (EINVAL);
	return (0);
}