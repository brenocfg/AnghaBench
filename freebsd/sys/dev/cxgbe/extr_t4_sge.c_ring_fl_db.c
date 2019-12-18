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
typedef  scalar_t__ uint32_t ;
struct sge_fl {int pidx; scalar_t__ dbval; int /*<<< orphan*/  sidx; int /*<<< orphan*/  dbidx; int /*<<< orphan*/ * udb; } ;
struct adapter {int /*<<< orphan*/  sge_kdoorbell_reg; } ;

/* Variables and functions */
 scalar_t__ IDXDIFF (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDXINCR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ V_PIDX (scalar_t__) ; 
 int /*<<< orphan*/  htole32 (scalar_t__) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
ring_fl_db(struct adapter *sc, struct sge_fl *fl)
{
	uint32_t n, v;

	n = IDXDIFF(fl->pidx / 8, fl->dbidx, fl->sidx);
	MPASS(n > 0);

	wmb();
	v = fl->dbval | V_PIDX(n);
	if (fl->udb)
		*fl->udb = htole32(v);
	else
		t4_write_reg(sc, sc->sge_kdoorbell_reg, v);
	IDXINCR(fl->dbidx, n, fl->sidx);
}