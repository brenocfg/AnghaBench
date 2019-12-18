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
struct spu_queue {int /*<<< orphan*/ * q; int /*<<< orphan*/  q_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_queue (int /*<<< orphan*/ ) ; 
 int spu_queue_register (struct spu_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spu_queue_setup(struct spu_queue *p)
{
	int err;

	p->q = new_queue(p->q_type);
	if (!p->q)
		return -ENOMEM;

	err = spu_queue_register(p, p->q_type);
	if (err) {
		free_queue(p->q, p->q_type);
		p->q = NULL;
	}

	return err;
}