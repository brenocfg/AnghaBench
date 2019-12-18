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
typedef  int /*<<< orphan*/  vmf ;
struct vm86frame {int vmf_eax; int vmf_edx; int vmf_ebx; int vmf_ecx; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct vm86frame*,int) ; 
 int /*<<< orphan*/  vm86_intcall (int,struct vm86frame*) ; 

__attribute__((used)) static int
int15_gsic_call(int *sig, int *smi_cmd, int *command, int *smi_data, int *flags)
{
	struct vm86frame vmf;

	bzero(&vmf, sizeof(vmf));
	vmf.vmf_eax = 0x0000E980;	/* IST support */
	vmf.vmf_edx = 0x47534943;	/* 'GSIC' in ASCII */
	vm86_intcall(0x15, &vmf);

	if (vmf.vmf_eax == 0x47534943) {
		*sig = vmf.vmf_eax;
		*smi_cmd = vmf.vmf_ebx & 0xff;
		*command = (vmf.vmf_ebx >> 16) & 0xff;
		*smi_data = vmf.vmf_ecx;
		*flags = vmf.vmf_edx;
	} else {
		*sig = -1;
		*smi_cmd = -1;
		*command = -1;
		*smi_data = -1;
		*flags = -1;
	}

	return (0);
}