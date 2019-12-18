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
typedef  int u_int32_t ;
struct sc_info {int cd2id; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  YDSXGR_AC97CMDDATA ; 
 int YDSXG_AC97WRITECMD ; 
 int ds_cdbusy (struct sc_info*,int) ; 
 int /*<<< orphan*/  ds_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ds_wrcd(kobj_t obj, void *devinfo, int regno, u_int32_t data)
{
	struct sc_info *sc = (struct sc_info *)devinfo;
	int sec, cid;
	u_int32_t cmd;

	sec = regno & 0x100;
	regno &= 0xff;
	cid = sec? (sc->cd2id << 8) : 0;
	if (sec && cid == 0)
		return ENXIO;

	cmd = YDSXG_AC97WRITECMD | cid | regno;
	cmd <<= 16;
	cmd |= data;
	ds_wr(sc, YDSXGR_AC97CMDDATA, cmd, 4);

	return ds_cdbusy(sc, sec);
}