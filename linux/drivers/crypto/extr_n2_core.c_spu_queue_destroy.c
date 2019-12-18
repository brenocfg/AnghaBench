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
struct spu_queue {int /*<<< orphan*/  q_type; int /*<<< orphan*/  q; int /*<<< orphan*/  qhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long sun4v_ncs_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_queue_destroy(struct spu_queue *p)
{
	unsigned long hv_ret;

	if (!p->q)
		return;

	hv_ret = sun4v_ncs_qconf(p->q_type, p->qhandle, 0, &p->qhandle);

	if (!hv_ret)
		free_queue(p->q, p->q_type);
}