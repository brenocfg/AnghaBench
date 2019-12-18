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
struct ata_channel {int /*<<< orphan*/  poll_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_interrupt (struct ata_channel*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ata_channel*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
ata_periodic_poll(void *data)
{
    struct ata_channel *ch = (struct ata_channel *)data;

    callout_reset(&ch->poll_callout, hz, ata_periodic_poll, ch);
    ata_interrupt(ch);
}