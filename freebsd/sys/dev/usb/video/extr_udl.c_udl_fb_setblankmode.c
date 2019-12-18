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
typedef  int /*<<< orphan*/  uint32_t ;
struct udl_softc {scalar_t__ sc_fb_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
#define  V_DISPLAY_BLANK 131 
#define  V_DISPLAY_ON 130 
#define  V_DISPLAY_STAND_BY 129 
#define  V_DISPLAY_SUSPEND 128 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  udl_get_fb_size (struct udl_softc*) ; 
 int /*<<< orphan*/  udl_power_save (struct udl_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udl_fb_setblankmode(void *arg, int mode)
{
	struct udl_softc *sc = arg;

	switch (mode) {
	case V_DISPLAY_ON:
		udl_power_save(sc, 1, M_WAITOK);
		break;
	case V_DISPLAY_BLANK:
		udl_power_save(sc, 1, M_WAITOK);
		if (sc->sc_fb_addr != 0) {
			const uint32_t max = udl_get_fb_size(sc);

			memset((void *)sc->sc_fb_addr, 0, max);
		}
		break;
	case V_DISPLAY_STAND_BY:
	case V_DISPLAY_SUSPEND:
		udl_power_save(sc, 0, M_WAITOK);
		break;
	}
	return (0);
}