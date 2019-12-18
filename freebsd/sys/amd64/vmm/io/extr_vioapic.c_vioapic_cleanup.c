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
struct vioapic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VIOAPIC ; 
 int /*<<< orphan*/  free (struct vioapic*,int /*<<< orphan*/ ) ; 

void
vioapic_cleanup(struct vioapic *vioapic)
{

	free(vioapic, M_VIOAPIC);
}