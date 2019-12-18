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
struct ntb_softc {int /*<<< orphan*/  device; int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_ntb_link_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_ntb_teardown_xeon(struct ntb_softc *ntb)
{

	if (ntb->reg != NULL)
		intel_ntb_link_disable(ntb->device);
}