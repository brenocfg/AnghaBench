#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_4__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_5__ {int recvsize; int in_maxrec; int /*<<< orphan*/  nonblock; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

bool_t
__xdrrec_setnonblock(XDR *xdrs, int maxrec)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);

	rstrm->nonblock = TRUE;
	if (maxrec == 0)
		maxrec = rstrm->recvsize;
	rstrm->in_maxrec = maxrec;
	return TRUE;
}