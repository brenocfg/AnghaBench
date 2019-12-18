#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int rm_firstdatacol; int rm_cols; TYPE_1__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_8__ {scalar_t__ rc_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int VDEV_RAIDZ_MAXPARITY ; 
 size_t VDEV_RAIDZ_P ; 
 size_t VDEV_RAIDZ_Q ; 
 int /*<<< orphan*/  vdev_raidz_default_to_general ; 
 int vdev_raidz_reconstruct_general (TYPE_2__*,int*,int) ; 
 int vdev_raidz_reconstruct_p (TYPE_2__*,int*,int) ; 
 int vdev_raidz_reconstruct_pq (TYPE_2__*,int*,int) ; 
 int vdev_raidz_reconstruct_q (TYPE_2__*,int*,int) ; 

__attribute__((used)) static int
vdev_raidz_reconstruct(raidz_map_t *rm, int *t, int nt)
{
	int tgts[VDEV_RAIDZ_MAXPARITY], *dt;
	int ntgts;
	int i, c;
	int code;
	int nbadparity, nbaddata;
	int parity_valid[VDEV_RAIDZ_MAXPARITY];

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
		if (c < rm->rm_firstdatacol)
			parity_valid[c] = B_FALSE;

		if (i < nt && c == t[i]) {
			tgts[ntgts++] = c;
			i++;
		} else if (rm->rm_col[c].rc_error != 0) {
			tgts[ntgts++] = c;
		} else if (c >= rm->rm_firstdatacol) {
			nbaddata--;
		} else {
			parity_valid[c] = B_TRUE;
			nbadparity--;
		}
	}

	ASSERT(ntgts >= nt);
	ASSERT(nbaddata >= 0);
	ASSERT(nbaddata + nbadparity == ntgts);

	dt = &tgts[nbadparity];

	/*
	 * See if we can use any of our optimized reconstruction routines.
	 */
	if (!vdev_raidz_default_to_general) {
		switch (nbaddata) {
		case 1:
			if (parity_valid[VDEV_RAIDZ_P])
				return (vdev_raidz_reconstruct_p(rm, dt, 1));

			ASSERT(rm->rm_firstdatacol > 1);

			if (parity_valid[VDEV_RAIDZ_Q])
				return (vdev_raidz_reconstruct_q(rm, dt, 1));

			ASSERT(rm->rm_firstdatacol > 2);
			break;

		case 2:
			ASSERT(rm->rm_firstdatacol > 1);

			if (parity_valid[VDEV_RAIDZ_P] &&
			    parity_valid[VDEV_RAIDZ_Q])
				return (vdev_raidz_reconstruct_pq(rm, dt, 2));

			ASSERT(rm->rm_firstdatacol > 2);

			break;
		}
	}

	code = vdev_raidz_reconstruct_general(rm, tgts, ntgts);
	ASSERT(code < (1 << VDEV_RAIDZ_MAXPARITY));
	ASSERT(code > 0);
	return (code);
}