#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sc_info {int* left; int* right; TYPE_1__* cfg; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int subvendor; int subdevice; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_MT_VOLIDX ; 
 int /*<<< orphan*/  ENVY24_MT_VOLUME ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
envy24_setvolume(struct sc_info *sc, unsigned ch)
{
#if(0)
	device_printf(sc->dev, "envy24_setvolume(sc, %d)\n", ch);
#endif
if (sc->cfg->subvendor==0x153b  && sc->cfg->subdevice==0x1138 ) {
        envy24_wrmt(sc, ENVY24_MT_VOLIDX, 16, 1);
        envy24_wrmt(sc, ENVY24_MT_VOLUME, 0x7f7f, 2);
        envy24_wrmt(sc, ENVY24_MT_VOLIDX, 17, 1);
        envy24_wrmt(sc, ENVY24_MT_VOLUME, 0x7f7f, 2);
	}

	envy24_wrmt(sc, ENVY24_MT_VOLIDX, ch * 2, 1);
	envy24_wrmt(sc, ENVY24_MT_VOLUME, 0x7f00 | sc->left[ch], 2);
	envy24_wrmt(sc, ENVY24_MT_VOLIDX, ch * 2 + 1, 1);
	envy24_wrmt(sc, ENVY24_MT_VOLUME, (sc->right[ch] << 8) | 0x7f, 2);
}