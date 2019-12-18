#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int rpcvers_t ;
typedef  size_t rpcproc_t ;
struct TYPE_2__ {int /*<<< orphan*/ * info; } ;

/* Variables and functions */
#define  PMAPVERS 130 
#define  RPCBVERS 129 
#define  RPCBVERS4 128 
 TYPE_1__* inf ; 
 size_t rpcb_highproc_2 ; 
 size_t rpcb_highproc_3 ; 
 size_t rpcb_highproc_4 ; 

void
rpcbs_procinfo(rpcvers_t rtype, rpcproc_t proc)
{
	switch (rtype + 2) {
#ifdef PORTMAP
	case PMAPVERS:		/* version 2 */
		if (proc > rpcb_highproc_2)
			return;
		break;
#endif
	case RPCBVERS:		/* version 3 */
		if (proc > rpcb_highproc_3)
			return;
		break;
	case RPCBVERS4:		/* version 4 */
		if (proc > rpcb_highproc_4)
			return;
		break;
	default: return;
	}
	inf[rtype].info[proc]++;
	return;
}