#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int q_len; } ;
struct snd_queue {int tail; TYPE_1__ dmem; int /*<<< orphan*/  free_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline int
nicvf_get_sq_desc(struct snd_queue *sq, int desc_cnt)
{
	int qentry;

	qentry = sq->tail;
	atomic_subtract_int(&sq->free_cnt, desc_cnt);
	sq->tail += desc_cnt;
	sq->tail &= (sq->dmem.q_len - 1);

	return (qentry);
}