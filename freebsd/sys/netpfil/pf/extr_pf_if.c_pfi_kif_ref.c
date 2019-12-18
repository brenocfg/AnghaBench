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
struct pfi_kif {int /*<<< orphan*/  pfik_rulerefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 

void
pfi_kif_ref(struct pfi_kif *kif)
{

	PF_RULES_WASSERT();
	kif->pfik_rulerefs++;
}