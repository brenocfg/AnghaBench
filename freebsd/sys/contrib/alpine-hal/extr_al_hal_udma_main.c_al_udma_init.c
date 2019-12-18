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
typedef  union udma_regs {int dummy; } udma_regs ;
struct al_udma_params {int num_of_queues; scalar_t__ type; char* name; TYPE_2__* udma_regs_base; } ;
struct al_udma {scalar_t__ type; int num_of_queues; char* name; union udma_regs* udma_regs; TYPE_1__* udma_q; int /*<<< orphan*/  state; int /*<<< orphan*/  rev_id; int /*<<< orphan*/ * gen_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  s2m; int /*<<< orphan*/  m2s; int /*<<< orphan*/  gen; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_QUEUE_NOT_INITIALIZED ; 
 int DMA_MAX_Q ; 
 int EINVAL ; 
 int /*<<< orphan*/  UDMA_DISABLE ; 
 scalar_t__ UDMA_TX ; 
 int /*<<< orphan*/  al_assert (struct al_udma*) ; 
 int /*<<< orphan*/  al_dbg (char*,char*,union udma_regs*) ; 
 int /*<<< orphan*/  al_err (char*) ; 
 int /*<<< orphan*/  al_udma_get_revision (TYPE_2__*) ; 
 int /*<<< orphan*/  al_udma_set_defaults (struct al_udma*) ; 

int al_udma_init(struct al_udma *udma, struct al_udma_params *udma_params)
{
	int i;

	al_assert(udma);

	if (udma_params->num_of_queues > DMA_MAX_Q) {
		al_err("udma: invalid num_of_queues parameter\n");
		return -EINVAL;
	}

	udma->type = udma_params->type;
	udma->num_of_queues = udma_params->num_of_queues;
	udma->gen_regs = &udma_params->udma_regs_base->gen;

	if (udma->type == UDMA_TX)
		udma->udma_regs = (union udma_regs *)&udma_params->udma_regs_base->m2s;
	else
		udma->udma_regs = (union udma_regs *)&udma_params->udma_regs_base->s2m;

	udma->rev_id = al_udma_get_revision(udma_params->udma_regs_base);

	if (udma_params->name == NULL)
		udma->name = "";
	else
		udma->name = udma_params->name;

	udma->state = UDMA_DISABLE;
	for (i = 0; i < DMA_MAX_Q; i++) {
		udma->udma_q[i].status = AL_QUEUE_NOT_INITIALIZED;
	}
	/* initialize configuration registers to correct values */
	al_udma_set_defaults(udma);
	al_dbg("udma [%s] initialized. base %p\n", udma->name,
		udma->udma_regs);
	return 0;
}