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
struct cbb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CARD_3V_CARD ; 
 int CARD_5V_CARD ; 
 int CARD_XV_CARD ; 
 int CARD_YV_CARD ; 
 int /*<<< orphan*/  CBB_SOCKET_CONTROL ; 
 int CBB_SOCKET_CTRL_VCCMASK ; 
#define  CBB_SOCKET_CTRL_VCC_3V 131 
#define  CBB_SOCKET_CTRL_VCC_5V 130 
#define  CBB_SOCKET_CTRL_VCC_XV 129 
#define  CBB_SOCKET_CTRL_VCC_YV 128 
 int cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_current_voltage(device_t brdev)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	uint32_t ctrl;
	
	ctrl = cbb_get(sc, CBB_SOCKET_CONTROL);
	switch (ctrl & CBB_SOCKET_CTRL_VCCMASK) {
	case CBB_SOCKET_CTRL_VCC_5V:
		return CARD_5V_CARD;
	case CBB_SOCKET_CTRL_VCC_3V:
		return CARD_3V_CARD;
	case CBB_SOCKET_CTRL_VCC_XV:
		return CARD_XV_CARD;
	case CBB_SOCKET_CTRL_VCC_YV:
		return CARD_YV_CARD;
	}
	return 0;
}