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
struct sc_info {int* left; int* right; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24HT_MT_VOLIDX ; 
 int /*<<< orphan*/  ENVY24HT_MT_VOLUME ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  envy24ht_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
envy24ht_setvolume(struct sc_info *sc, unsigned ch)
{
#if(0)
	device_printf(sc->dev, "envy24ht_setvolume(sc, %d)\n", ch);
	envy24ht_wrmt(sc, ENVY24HT_MT_VOLIDX, ch * 2, 1);
	envy24ht_wrmt(sc, ENVY24HT_MT_VOLUME, 0x7f00 | sc->left[ch], 2);
	envy24ht_wrmt(sc, ENVY24HT_MT_VOLIDX, ch * 2 + 1, 1);
	envy24ht_wrmt(sc, ENVY24HT_MT_VOLUME, (sc->right[ch] << 8) | 0x7f, 2);
#endif
}