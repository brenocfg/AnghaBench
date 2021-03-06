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
struct bcma_intr {int /*<<< orphan*/  i_sel; int /*<<< orphan*/  i_mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  free (struct bcma_intr*,int /*<<< orphan*/ ) ; 

void
bcma_free_intr(struct bcma_intr *intr)
{
	KASSERT(!intr->i_mapped, ("interrupt %u still mapped", intr->i_sel));

	free(intr, M_BHND);
}