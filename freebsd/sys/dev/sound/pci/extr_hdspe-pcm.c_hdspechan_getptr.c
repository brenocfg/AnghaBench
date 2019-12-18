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
struct sc_pcminfo {struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {struct sc_pcminfo* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int HDSPE_BUF_POSITION_MASK ; 
 int /*<<< orphan*/  HDSPE_STATUS_REG ; 
 int hdspe_read_2 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
hdspechan_getptr(kobj_t obj, void *data)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sc_info *sc;
	uint32_t ret, pos;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;

	snd_mtxlock(sc->lock);
	ret = hdspe_read_2(sc, HDSPE_STATUS_REG);
	snd_mtxunlock(sc->lock);

	pos = ret & HDSPE_BUF_POSITION_MASK;
	pos *= 2; /* Hardbuf twice bigger. */

	return (pos);
}