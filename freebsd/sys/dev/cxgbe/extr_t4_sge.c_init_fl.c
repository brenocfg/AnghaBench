#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sge_fl {int qsize; int sidx; int /*<<< orphan*/  flags; int /*<<< orphan*/  lockname; } ;
struct TYPE_3__ {int spg_len; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {int flags; TYPE_2__ params; } ;

/* Variables and functions */
 int BUF_PACKING_OK ; 
 int EQ_ESIZE ; 
 int /*<<< orphan*/  FL_BUF_PACKING ; 
 int buffer_packing ; 
 int /*<<< orphan*/  find_best_refill_source (struct adapter*,struct sge_fl*,int) ; 
 int /*<<< orphan*/  find_safe_refill_source (struct adapter*,struct sge_fl*) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline void
init_fl(struct adapter *sc, struct sge_fl *fl, int qsize, int maxp, char *name)
{

	fl->qsize = qsize;
	fl->sidx = qsize - sc->params.sge.spg_len / EQ_ESIZE;
	strlcpy(fl->lockname, name, sizeof(fl->lockname));
	if (sc->flags & BUF_PACKING_OK &&
	    ((!is_t4(sc) && buffer_packing) ||	/* T5+: enabled unless 0 */
	    (is_t4(sc) && buffer_packing == 1)))/* T4: disabled unless 1 */
		fl->flags |= FL_BUF_PACKING;
	find_best_refill_source(sc, fl, maxp);
	find_safe_refill_source(sc, fl);
}