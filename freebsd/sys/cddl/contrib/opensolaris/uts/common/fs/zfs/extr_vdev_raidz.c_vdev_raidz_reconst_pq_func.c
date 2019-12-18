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
struct reconst_pq_struct {int* p; int* q; int* pxy; int* qxy; int /*<<< orphan*/  bexp; int /*<<< orphan*/  aexp; } ;

/* Variables and functions */
 int vdev_raidz_exp2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_raidz_reconst_pq_func(void *xbuf, void *ybuf, size_t size, void *private)
{
	struct reconst_pq_struct *rpq = private;
	uint8_t *xd = xbuf;
	uint8_t *yd = ybuf;

	for (int i = 0; i < size;
	    i++, rpq->p++, rpq->q++, rpq->pxy++, rpq->qxy++, xd++, yd++) {
		*xd = vdev_raidz_exp2(*rpq->p ^ *rpq->pxy, rpq->aexp) ^
		    vdev_raidz_exp2(*rpq->q ^ *rpq->qxy, rpq->bexp);
		*yd = *rpq->p ^ *rpq->pxy ^ *xd;
	}

	return (0);
}