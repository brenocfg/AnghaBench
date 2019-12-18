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
struct memwin {int mw_curpos; int mw_aperture; int mw_base; int /*<<< orphan*/  mw_lock; } ;
struct adapter {struct memwin* memwin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NUM_MEMWIN ; 
 int /*<<< orphan*/  RA_RLOCKED ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  le32toh (int) ; 
 int /*<<< orphan*/  position_memwin (struct adapter*,int,int) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_downgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_try_upgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int t4_read_reg (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int /*<<< orphan*/ ) ; 

int
rw_via_memwin(struct adapter *sc, int idx, uint32_t addr, uint32_t *val,
    int len, int rw)
{
	struct memwin *mw;
	uint32_t mw_end, v;

	MPASS(idx >= 0 && idx < NUM_MEMWIN);

	/* Memory can only be accessed in naturally aligned 4 byte units */
	if (addr & 3 || len & 3 || len <= 0)
		return (EINVAL);

	mw = &sc->memwin[idx];
	while (len > 0) {
		rw_rlock(&mw->mw_lock);
		mw_end = mw->mw_curpos + mw->mw_aperture;
		if (addr >= mw_end || addr < mw->mw_curpos) {
			/* Will need to reposition the window */
			if (!rw_try_upgrade(&mw->mw_lock)) {
				rw_runlock(&mw->mw_lock);
				rw_wlock(&mw->mw_lock);
			}
			rw_assert(&mw->mw_lock, RA_WLOCKED);
			position_memwin(sc, idx, addr);
			rw_downgrade(&mw->mw_lock);
			mw_end = mw->mw_curpos + mw->mw_aperture;
		}
		rw_assert(&mw->mw_lock, RA_RLOCKED);
		while (addr < mw_end && len > 0) {
			if (rw == 0) {
				v = t4_read_reg(sc, mw->mw_base + addr -
				    mw->mw_curpos);
				*val++ = le32toh(v);
			} else {
				v = *val++;
				t4_write_reg(sc, mw->mw_base + addr -
				    mw->mw_curpos, htole32(v));
			}
			addr += 4;
			len -= 4;
		}
		rw_runlock(&mw->mw_lock);
	}

	return (0);
}