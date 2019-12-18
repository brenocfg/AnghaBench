#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct qual {scalar_t__ dir; int /*<<< orphan*/  proto; int /*<<< orphan*/  addr; } ;
struct block {int dummy; } ;
struct TYPE_5__ {int linktype; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
#define  DLT_ARCNET 129 
#define  DLT_ARCNET_LINUX 128 
 int /*<<< orphan*/  Q_DEFAULT ; 
 int /*<<< orphan*/  Q_HOST ; 
 int /*<<< orphan*/  Q_LINK ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 struct block* gen_ahostop (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

struct block *
gen_acode(compiler_state_t *cstate, const u_char *eaddr, struct qual q)
{
	switch (cstate->linktype) {

	case DLT_ARCNET:
	case DLT_ARCNET_LINUX:
		if ((q.addr == Q_HOST || q.addr == Q_DEFAULT) &&
		    q.proto == Q_LINK)
			return (gen_ahostop(cstate, eaddr, (int)q.dir));
		else {
			bpf_error(cstate, "ARCnet address used in non-arc expression");
			/* NOTREACHED */
		}
		break;

	default:
		bpf_error(cstate, "aid supported only on ARCnet");
		/* NOTREACHED */
	}
}