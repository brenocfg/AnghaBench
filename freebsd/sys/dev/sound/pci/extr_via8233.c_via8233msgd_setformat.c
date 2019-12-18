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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct via_info {int /*<<< orphan*/  lock; } ;
struct via_chinfo {struct via_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int) ; 
 int AFMT_S16_LE ; 
 int MC_SGD_16BIT ; 
 int MC_SGD_8BIT ; 
 int MC_SGD_CHANNELS (int) ; 
 int SLOT3 (int) ; 
 int SLOT4 (int) ; 
 int /*<<< orphan*/  VIA_MC_SGD_FORMAT ; 
 int /*<<< orphan*/  VIA_MC_SLOT_SELECT ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_wr (struct via_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
via8233msgd_setformat(kobj_t obj, void *data, uint32_t format)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;

	uint32_t s = 0xff000000;
	uint8_t  v = (format & AFMT_S16_LE) ? MC_SGD_16BIT : MC_SGD_8BIT;

	if (AFMT_CHANNEL(format) > 1) {
		v |= MC_SGD_CHANNELS(2);
		s |= SLOT3(1) | SLOT4(2);
	} else {
		v |= MC_SGD_CHANNELS(1);
		s |= SLOT3(1) | SLOT4(1);
	}

	snd_mtxlock(via->lock);
	via_wr(via, VIA_MC_SLOT_SELECT, s, 4);
	via_wr(via, VIA_MC_SGD_FORMAT, v, 1);
	snd_mtxunlock(via->lock);

	return (0);
}