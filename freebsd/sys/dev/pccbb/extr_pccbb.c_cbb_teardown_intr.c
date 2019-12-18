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
struct cbb_intrhand {int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_TEARDOWN_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cbb_intrhand*,int /*<<< orphan*/ ) ; 

int
cbb_teardown_intr(device_t dev, device_t child, struct resource *irq,
    void *cookie)
{
	struct cbb_intrhand *ih;
	int err;

	/* XXX Need to do different things for ISA interrupts. */
	ih = (struct cbb_intrhand *) cookie;
	err = BUS_TEARDOWN_INTR(device_get_parent(dev), child, irq,
	    ih->cookie);
	if (err != 0)
		return (err);
	free(ih, M_DEVBUF);
	return (0);
}