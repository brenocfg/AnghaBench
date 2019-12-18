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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_6__ {scalar_t__ out_finger; scalar_t__ out_boundry; int /*<<< orphan*/  frag_sent; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  flush_out (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
xdrrec_putlong(XDR *xdrs, const long *lp)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	int32_t *dest_lp = ((int32_t *)(void *)(rstrm->out_finger));

	if ((rstrm->out_finger += sizeof(int32_t)) > rstrm->out_boundry) {
		/*
		 * this case should almost never happen so the code is
		 * inefficient
		 */
		rstrm->out_finger -= sizeof(int32_t);
		rstrm->frag_sent = TRUE;
		if (! flush_out(rstrm, FALSE))
			return (FALSE);
		dest_lp = ((int32_t *)(void *)(rstrm->out_finger));
		rstrm->out_finger += sizeof(int32_t);
	}
	*dest_lp = (int32_t)htonl((u_int32_t)(*lp));
	return (TRUE);
}