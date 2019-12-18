#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  src ;
struct TYPE_5__ {int rm_firstdatacol; int rm_cols; TYPE_1__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_4__ {int rc_size; int* rc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  VDEV_RAIDZ_64MUL_2 (int,int) ; 
 size_t VDEV_RAIDZ_P ; 
 size_t VDEV_RAIDZ_Q ; 

__attribute__((used)) static void
vdev_raidz_generate_parity_pq(raidz_map_t *rm)
{
	uint64_t *p, *q, *src, pcnt, ccnt, mask, i;
	int c;

	pcnt = rm->rm_col[VDEV_RAIDZ_P].rc_size / sizeof (src[0]);
	ASSERT(rm->rm_col[VDEV_RAIDZ_P].rc_size ==
	    rm->rm_col[VDEV_RAIDZ_Q].rc_size);

	for (c = rm->rm_firstdatacol; c < rm->rm_cols; c++) {
		src = rm->rm_col[c].rc_data;
		p = rm->rm_col[VDEV_RAIDZ_P].rc_data;
		q = rm->rm_col[VDEV_RAIDZ_Q].rc_data;

		ccnt = rm->rm_col[c].rc_size / sizeof (src[0]);

		if (c == rm->rm_firstdatacol) {
			ASSERT(ccnt == pcnt || ccnt == 0);
			for (i = 0; i < ccnt; i++, src++, p++, q++) {
				*p = *src;
				*q = *src;
			}
			for (; i < pcnt; i++, src++, p++, q++) {
				*p = 0;
				*q = 0;
			}
		} else {
			ASSERT(ccnt <= pcnt);

			/*
			 * Apply the algorithm described above by multiplying
			 * the previous result and adding in the new value.
			 */
			for (i = 0; i < ccnt; i++, src++, p++, q++) {
				*p ^= *src;

				VDEV_RAIDZ_64MUL_2(*q, mask);
				*q ^= *src;
			}

			/*
			 * Treat short columns as though they are full of 0s.
			 * Note that there's therefore nothing needed for P.
			 */
			for (; i < pcnt; i++, q++) {
				VDEV_RAIDZ_64MUL_2(*q, mask);
			}
		}
	}
}