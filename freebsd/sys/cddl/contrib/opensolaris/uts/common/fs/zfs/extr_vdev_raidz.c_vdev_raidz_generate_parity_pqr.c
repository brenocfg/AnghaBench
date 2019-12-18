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
typedef  size_t uint64_t ;
struct pqr_struct {size_t* member_0; size_t* member_1; size_t* member_2; } ;
struct TYPE_5__ {int rm_firstdatacol; int rm_cols; TYPE_1__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_4__ {int rc_size; int /*<<< orphan*/ * rc_abd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  VDEV_RAIDZ_64MUL_2 (size_t,size_t) ; 
 int /*<<< orphan*/  VDEV_RAIDZ_64MUL_4 (size_t,size_t) ; 
 size_t VDEV_RAIDZ_P ; 
 size_t VDEV_RAIDZ_Q ; 
 size_t VDEV_RAIDZ_R ; 
 int /*<<< orphan*/  abd_copy_to_buf (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct pqr_struct*) ; 
 size_t* abd_to_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  vdev_raidz_pqr_func ; 

__attribute__((used)) static void
vdev_raidz_generate_parity_pqr(raidz_map_t *rm)
{
	uint64_t *p, *q, *r, pcnt, ccnt, mask, i;
	int c;
	abd_t *src;

	pcnt = rm->rm_col[VDEV_RAIDZ_P].rc_size / sizeof (p[0]);
	ASSERT(rm->rm_col[VDEV_RAIDZ_P].rc_size ==
	    rm->rm_col[VDEV_RAIDZ_Q].rc_size);
	ASSERT(rm->rm_col[VDEV_RAIDZ_P].rc_size ==
	    rm->rm_col[VDEV_RAIDZ_R].rc_size);

	for (c = rm->rm_firstdatacol; c < rm->rm_cols; c++) {
		src = rm->rm_col[c].rc_abd;
		p = abd_to_buf(rm->rm_col[VDEV_RAIDZ_P].rc_abd);
		q = abd_to_buf(rm->rm_col[VDEV_RAIDZ_Q].rc_abd);
		r = abd_to_buf(rm->rm_col[VDEV_RAIDZ_R].rc_abd);

		ccnt = rm->rm_col[c].rc_size / sizeof (p[0]);

		if (c == rm->rm_firstdatacol) {
			abd_copy_to_buf(p, src, rm->rm_col[c].rc_size);
			(void) memcpy(q, p, rm->rm_col[c].rc_size);
			(void) memcpy(r, p, rm->rm_col[c].rc_size);
		} else {
			struct pqr_struct pqr = { p, q, r };
			(void) abd_iterate_func(src, 0, rm->rm_col[c].rc_size,
			    vdev_raidz_pqr_func, &pqr);
		}

		if (c == rm->rm_firstdatacol) {
			for (i = ccnt; i < pcnt; i++) {
				p[i] = 0;
				q[i] = 0;
				r[i] = 0;
			}
		} else {
			/*
			 * Treat short columns as though they are full of 0s.
			 * Note that there's therefore nothing needed for P.
			 */
			for (i = ccnt; i < pcnt; i++) {
				VDEV_RAIDZ_64MUL_2(q[i], mask);
				VDEV_RAIDZ_64MUL_4(r[i], mask);
			}
		}
	}
}