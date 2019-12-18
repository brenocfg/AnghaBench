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
struct ata_channel {int /*<<< orphan*/  state_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_interrupt_locked (void*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
ata_interrupt(void *data)
{
    struct ata_channel *ch = (struct ata_channel *)data;

    mtx_lock(&ch->state_mtx);
    ata_interrupt_locked(data);
    mtx_unlock(&ch->state_mtx);
}