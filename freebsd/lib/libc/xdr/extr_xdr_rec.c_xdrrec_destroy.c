#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_6__ {int sendsize; int recvsize; struct TYPE_6__* in_base; struct TYPE_6__* out_base; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free (TYPE_2__*,int) ; 

__attribute__((used)) static void
xdrrec_destroy(XDR *xdrs)
{
	RECSTREAM *rstrm = (RECSTREAM *)xdrs->x_private;

	mem_free(rstrm->out_base, rstrm->sendsize);
	mem_free(rstrm->in_base, rstrm->recvsize);
	mem_free(rstrm, sizeof(RECSTREAM));
}