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
struct sc_pchinfo {int spd; scalar_t__ dac_data; int /*<<< orphan*/  dac_idx; struct sc_info* parent; } ;
struct sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ CDATA_FREQUENCY ; 
 int /*<<< orphan*/  CHANGE ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  m3_wr_assp_data (struct sc_info*,scalar_t__,int) ; 

__attribute__((used)) static u_int32_t
m3_pchan_setspeed(kobj_t kobj, void *chdata, u_int32_t speed)
{
	struct sc_pchinfo *ch = chdata;
	struct sc_info *sc = ch->parent;
	u_int32_t freq;

	M3_LOCK(sc);
	M3_DEBUG(CHANGE, ("m3_pchan_setspeed(dac=%d, speed=%d)\n",
			  ch->dac_idx, speed));

        if ((freq = ((speed << 15) + 24000) / 48000) != 0) {
                freq--;
        }

        m3_wr_assp_data(sc, ch->dac_data + CDATA_FREQUENCY, freq);
	ch->spd = speed;
	M3_UNLOCK(sc);

	/* return closest possible speed */
	return (speed);
}