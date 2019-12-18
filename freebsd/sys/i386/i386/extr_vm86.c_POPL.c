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
typedef  int /*<<< orphan*/  u_int ;
struct vm86frame {int vmf_sp; int /*<<< orphan*/  vmf_ss; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_ADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm86_fuword (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline u_int
POPL(struct vm86frame *vmf)
{
	u_int x = vm86_fuword(MAKE_ADDR(vmf->vmf_ss, vmf->vmf_sp));

	vmf->vmf_sp += 4;
	return (x);
}