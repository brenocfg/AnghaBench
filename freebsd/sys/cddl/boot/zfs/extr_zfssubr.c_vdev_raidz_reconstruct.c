#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rm_firstdatacol; int rm_cols; TYPE_1__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_5__ {scalar_t__ rc_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int VDEV_RAIDZ_MAXPARITY ; 
 int vdev_raidz_reconstruct_general (TYPE_2__*,int*,int) ; 

__attribute__((used)) static int
vdev_raidz_reconstruct(raidz_map_t *rm, int *t, int nt)
{
	int tgts[VDEV_RAIDZ_MAXPARITY];
	int ntgts;
	int i, c;
	int code;
	int nbadparity, nbaddata;

	/*
	 * The tgts list must already be sorted.
	 */
	for (i = 1; i < nt; i++) {
		ASSERT(t[i] > t[i - 1]);
	}

	nbadparity = rm->rm_firstdatacol;
	nbaddata = rm->rm_cols - nbadparity;
	ntgts = 0;
	for (i = 0, c = 0; c < rm->rm_cols; c++) {
		if (i < nt && c == t[i]) {
			tgts[ntgts++] = c;
			i++;
		} else if (rm->rm_col[c].rc_error != 0) {
			tgts[ntgts++] = c;
		} else if (c >= rm->rm_firstdatacol) {
			nbaddata--;
		} else {
			nbadparity--;
		}
	}

	ASSERT(ntgts >= nt);
	ASSERT(nbaddata >= 0);
	ASSERT(nbaddata + nbadparity == ntgts);

	code = vdev_raidz_reconstruct_general(rm, tgts, ntgts);
	ASSERT(code < (1 << VDEV_RAIDZ_MAXPARITY));
	ASSERT(code > 0);
	return (code);
}