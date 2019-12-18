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
struct pf_addr_wrap {int type; } ;

/* Variables and functions */
#define  PF_ADDR_DYNIFTL 129 
#define  PF_ADDR_TABLE 128 
 int /*<<< orphan*/  pf_tbladdr_copyout (struct pf_addr_wrap*) ; 
 int /*<<< orphan*/  pfi_dynaddr_copyout (struct pf_addr_wrap*) ; 

__attribute__((used)) static void
pf_addr_copyout(struct pf_addr_wrap *addr)
{

	switch (addr->type) {
	case PF_ADDR_DYNIFTL:
		pfi_dynaddr_copyout(addr);
		break;
	case PF_ADDR_TABLE:
		pf_tbladdr_copyout(addr);
		break;
	}
}