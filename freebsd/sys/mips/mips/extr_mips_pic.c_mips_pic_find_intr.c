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
struct resource {int dummy; } ;
struct mips_pic_intr {scalar_t__ intr_irq; } ;
typedef  scalar_t__ rman_res_t ;

/* Variables and functions */
 struct mips_pic_intr* mips_pic_intrs ; 
 int /*<<< orphan*/  mips_pic_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 size_t nitems (struct mips_pic_intr*) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 int rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static struct mips_pic_intr *
mips_pic_find_intr(struct resource *r)
{
	struct mips_pic_intr	*intr;
	rman_res_t		 irq;

	irq = rman_get_start(r);
	if (irq != rman_get_end(r) || rman_get_size(r) != 1)
		return (NULL);

	mtx_lock(&mips_pic_mtx);
	for (size_t i = 0; i < nitems(mips_pic_intrs); i++) {
		intr = &mips_pic_intrs[i];

		if (intr->intr_irq != irq)
			continue;

		mtx_unlock(&mips_pic_mtx);
		return (intr);
	}
	mtx_unlock(&mips_pic_mtx);

	/* Not found */
	return (NULL);
}