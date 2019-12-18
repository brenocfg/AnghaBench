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
struct mips_pic_intr {scalar_t__ consumers; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ UINT_MAX ; 
 int intr_activate_irq (int /*<<< orphan*/ ,struct resource*) ; 
 struct mips_pic_intr* mips_pic_find_intr (struct resource*) ; 
 int /*<<< orphan*/  mips_pic_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
mips_pic_activate_intr(device_t child, struct resource *r)
{
	struct mips_pic_intr	*intr;
	int			 error;

	/* Is this one of our shared MIPS interrupts? */
	if ((intr = mips_pic_find_intr(r)) == NULL) {
		/* Delegate to standard INTRNG activation */
		return (intr_activate_irq(child, r));
	}

	/* Bump consumer count and request activation if required */
	mtx_lock(&mips_pic_mtx);
	if (intr->consumers == UINT_MAX) {
		mtx_unlock(&mips_pic_mtx);
		return (ENOMEM);
	}

	if (intr->consumers == 0) {
		if ((error = intr_activate_irq(child, r))) {
			mtx_unlock(&mips_pic_mtx);
			return (error);
		}
	}

	intr->consumers++;
	mtx_unlock(&mips_pic_mtx);

	return (0);
}