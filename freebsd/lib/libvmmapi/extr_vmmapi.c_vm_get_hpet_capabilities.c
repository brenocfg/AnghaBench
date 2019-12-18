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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_hpet_cap {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_HPET_CAPABILITIES ; 
 int /*<<< orphan*/  bzero (struct vm_hpet_cap*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_hpet_cap*) ; 

int
vm_get_hpet_capabilities(struct vmctx *ctx, uint32_t *capabilities)
{
	int error;
	struct vm_hpet_cap cap;

	bzero(&cap, sizeof(struct vm_hpet_cap));
	error = ioctl(ctx->fd, VM_GET_HPET_CAPABILITIES, &cap);
	if (capabilities != NULL)
		*capabilities = cap.capabilities;
	return (error);
}