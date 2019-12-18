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
struct ahci_channel {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
ahci_putch(struct ahci_channel *ch)
{

	mtx_unlock(&ch->mtx);
}