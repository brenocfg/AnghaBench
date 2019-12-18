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
typedef  scalar_t__ u_int32_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_CONFIG ; 
 scalar_t__ YDSXG_WORKBITTIMEOUT ; 
 int ds_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ds_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ds_enadsp(struct sc_info *sc, int on)
{
	u_int32_t v, i;

	v = on? 1 : 0;
	if (on) {
		ds_wr(sc, YDSXGR_CONFIG, 0x00000001, 4);
	} else {
		if (ds_rd(sc, YDSXGR_CONFIG, 4))
			ds_wr(sc, YDSXGR_CONFIG, 0x00000000, 4);
		i = YDSXG_WORKBITTIMEOUT;
		while (i > 0) {
			if (!(ds_rd(sc, YDSXGR_CONFIG, 4) & 0x00000002))
				break;
			i--;
		}
	}
}