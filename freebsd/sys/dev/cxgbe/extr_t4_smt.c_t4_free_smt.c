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
struct smt_data {int smt_size; int /*<<< orphan*/  lock; TYPE_1__* smtab; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  free (struct smt_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 

int
t4_free_smt(struct smt_data *s)
{
	int i;

	for (i = 0; i < s->smt_size; i++)
		mtx_destroy(&s->smtab[i].lock);
	rw_destroy(&s->lock);
	free(s, M_CXGBE);

	return (0);
}