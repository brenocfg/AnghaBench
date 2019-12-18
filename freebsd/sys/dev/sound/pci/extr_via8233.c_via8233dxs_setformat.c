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
struct via_info {int /*<<< orphan*/  lock; } ;
struct via_chinfo {int rbase; struct via_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 
 int VIA8233_DXS_RATEFMT_16BIT ; 
 int VIA8233_DXS_RATEFMT_STEREO ; 
 int VIA8233_RP_DXS_RATEFMT ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int via_rd (struct via_info*,int,int) ; 
 int /*<<< orphan*/  via_wr (struct via_info*,int,int,int) ; 

__attribute__((used)) static int
via8233dxs_setformat(kobj_t obj, void *data, uint32_t format)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;
	uint32_t r, v;

	r = ch->rbase + VIA8233_RP_DXS_RATEFMT;
	snd_mtxlock(via->lock);
	v = via_rd(via, r, 4);

	v &= ~(VIA8233_DXS_RATEFMT_STEREO | VIA8233_DXS_RATEFMT_16BIT);
	if (AFMT_CHANNEL(format) > 1)
		v |= VIA8233_DXS_RATEFMT_STEREO;
	if (format & AFMT_16BIT)
		v |= VIA8233_DXS_RATEFMT_16BIT;
	via_wr(via, r, v, 4);
	snd_mtxunlock(via->lock);

	return (0);
}