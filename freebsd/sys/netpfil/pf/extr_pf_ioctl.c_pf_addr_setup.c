#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pf_ruleset {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  tblname; } ;
struct pf_addr_wrap {int type; TYPE_2__ p; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int ENOMEM ; 
#define  PF_ADDR_DYNIFTL 129 
#define  PF_ADDR_TABLE 128 
 int pfi_dynaddr_setup (struct pf_addr_wrap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pfr_attach_table (struct pf_ruleset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pf_addr_setup(struct pf_ruleset *ruleset, struct pf_addr_wrap *addr,
    sa_family_t af)
{
	int error = 0;

	switch (addr->type) {
	case PF_ADDR_TABLE:
		addr->p.tbl = pfr_attach_table(ruleset, addr->v.tblname);
		if (addr->p.tbl == NULL)
			error = ENOMEM;
		break;
	case PF_ADDR_DYNIFTL:
		error = pfi_dynaddr_setup(addr, af);
		break;
	}

	return (error);
}