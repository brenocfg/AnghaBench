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
typedef  unsigned int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_MT_VOLIDX ; 
 int /*<<< orphan*/  ENVY24_MT_VOLUME ; 
 int ENVY24_VOL_MUTE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void
envy24_mutevolume(struct sc_info *sc, unsigned ch)
{
	u_int32_t vol;

#if(0)
	device_printf(sc->dev, "envy24_mutevolume(sc, %d)\n", ch);
#endif
	vol = ENVY24_VOL_MUTE << 8 | ENVY24_VOL_MUTE;
	envy24_wrmt(sc, ENVY24_MT_VOLIDX, ch * 2, 1);
	envy24_wrmt(sc, ENVY24_MT_VOLUME, vol, 2);
	envy24_wrmt(sc, ENVY24_MT_VOLIDX, ch * 2 + 1, 1);
	envy24_wrmt(sc, ENVY24_MT_VOLUME, vol, 2);
}