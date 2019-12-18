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
struct sc_pchinfo {int fmt; scalar_t__ dac_data; int /*<<< orphan*/  dac_idx; struct sc_info* parent; } ;
struct sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int) ; 
 int AFMT_S8 ; 
 int AFMT_U8 ; 
 int /*<<< orphan*/  CHANGE ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 scalar_t__ SRC3_MODE_OFFSET ; 
 scalar_t__ SRC3_WORD_LENGTH_OFFSET ; 
 int /*<<< orphan*/  m3_wr_assp_data (struct sc_info*,scalar_t__,int) ; 

__attribute__((used)) static int
m3_pchan_setformat(kobj_t kobj, void *chdata, u_int32_t format)
{
	struct sc_pchinfo *ch = chdata;
	struct sc_info *sc = ch->parent;
	u_int32_t data;

	M3_LOCK(sc);
	M3_DEBUG(CHANGE,
		 ("m3_pchan_setformat(dac=%d, format=0x%x{%s-%s})\n",
		  ch->dac_idx, format,
		  format & (AFMT_U8|AFMT_S8) ? "8bit":"16bit",
		  (AFMT_CHANNEL(format) > 1) ? "STEREO":"MONO"));

	/* mono word */
        data = (AFMT_CHANNEL(format) > 1)? 0 : 1;
        m3_wr_assp_data(sc, ch->dac_data + SRC3_MODE_OFFSET, data);

        /* 8bit word */
        data = ((format & AFMT_U8) || (format & AFMT_S8)) ? 1 : 0;
        m3_wr_assp_data(sc, ch->dac_data + SRC3_WORD_LENGTH_OFFSET, data);

        ch->fmt = format;
	M3_UNLOCK(sc);

        return (0);
}