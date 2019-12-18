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
struct vmctx {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_IOAPIC_PINCOUNT ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
vm_ioapic_pincount(struct vmctx *ctx, int *pincount)
{

	return (ioctl(ctx->fd, VM_IOAPIC_PINCOUNT, pincount));
}