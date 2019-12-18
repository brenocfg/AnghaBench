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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct vmcs {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VMCLEAR (struct vmcs*) ; 
 int /*<<< orphan*/  VMPTRLD (struct vmcs*) ; 
 int vmcs_field_encoding (int) ; 
 int /*<<< orphan*/  vmcs_fix_regval (int,int /*<<< orphan*/ ) ; 
 int vmwrite (int,int /*<<< orphan*/ ) ; 

int
vmcs_setreg(struct vmcs *vmcs, int running, int ident, uint64_t val)
{
	int error;
	uint32_t encoding;

	if (ident < 0)
		encoding = ident & 0x7fffffff;
	else
		encoding = vmcs_field_encoding(ident);

	if (encoding == (uint32_t)-1)
		return (EINVAL);

	val = vmcs_fix_regval(encoding, val);

	if (!running)
		VMPTRLD(vmcs);

	error = vmwrite(encoding, val);

	if (!running)
		VMCLEAR(vmcs);

	return (error);
}