#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  keyboard; } ;
typedef  TYPE_1__ sc_softc_t ;
typedef  int /*<<< orphan*/  ki ;
struct TYPE_11__ {int /*<<< orphan*/  kb_unit; int /*<<< orphan*/  kb_name; } ;
typedef  TYPE_2__ keyboard_t ;
struct TYPE_12__ {int /*<<< orphan*/  kb_unit; int /*<<< orphan*/  kb_name; } ;
typedef  TYPE_3__ keyboard_info_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBADDKBD ; 
 scalar_t__ KBD_IS_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int kbd_allocate (char*,int,void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int kbd_find_keyboard2 (char*,int,int) ; 
 TYPE_2__* kbd_get_keyboard (int) ; 
 int /*<<< orphan*/  kbdd_ioctl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sckbdevent ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sc_allocate_keyboard(sc_softc_t *sc, int unit)
{
	int		 idx0, idx;
	keyboard_t	*k0, *k;
	keyboard_info_t	 ki;

	idx0 = kbd_allocate("kbdmux", -1, (void *)&sc->keyboard, sckbdevent, sc);
	if (idx0 != -1) {
		k0 = kbd_get_keyboard(idx0);

		for (idx = kbd_find_keyboard2("*", -1, 0);
		     idx != -1;
		     idx = kbd_find_keyboard2("*", -1, idx + 1)) {
			k = kbd_get_keyboard(idx);

			if (idx == idx0 || KBD_IS_BUSY(k))
				continue;

			bzero(&ki, sizeof(ki));
			strcpy(ki.kb_name, k->kb_name);
			ki.kb_unit = k->kb_unit;

			(void)kbdd_ioctl(k0, KBADDKBD, (caddr_t) &ki);
		}
	} else
		idx0 = kbd_allocate("*", unit, (void *)&sc->keyboard, sckbdevent, sc);

	return (idx0);
}