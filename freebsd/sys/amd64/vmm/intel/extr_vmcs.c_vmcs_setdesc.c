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
typedef  scalar_t__ uint32_t ;
struct vmcs {int dummy; } ;
struct seg_desc {int /*<<< orphan*/  access; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCLEAR (struct vmcs*) ; 
 scalar_t__ VMCS_INVALID_ENCODING ; 
 int /*<<< orphan*/  VMPTRLD (struct vmcs*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int vmcs_seg_desc_encoding (int,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int vmwrite (scalar_t__,int /*<<< orphan*/ ) ; 

int
vmcs_setdesc(struct vmcs *vmcs, int running, int seg, struct seg_desc *desc)
{
	int error;
	uint32_t base, limit, access;

	error = vmcs_seg_desc_encoding(seg, &base, &limit, &access);
	if (error != 0)
		panic("vmcs_setdesc: invalid segment register %d", seg);

	if (!running)
		VMPTRLD(vmcs);
	if ((error = vmwrite(base, desc->base)) != 0)
		goto done;

	if ((error = vmwrite(limit, desc->limit)) != 0)
		goto done;

	if (access != VMCS_INVALID_ENCODING) {
		if ((error = vmwrite(access, desc->access)) != 0)
			goto done;
	}
done:
	if (!running)
		VMCLEAR(vmcs);
	return (error);
}