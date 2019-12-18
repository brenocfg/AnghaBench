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
typedef  scalar_t__ u_long ;
typedef  int u_int32_t ;
typedef  scalar_t__ bool_t ;
struct TYPE_5__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_6__ {int* frag_header; scalar_t__ out_finger; scalar_t__ frag_sent; scalar_t__ out_boundry; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LAST_FRAG ; 
 scalar_t__ TRUE ; 
 scalar_t__ flush_out (TYPE_2__*,scalar_t__) ; 
 int htonl (int) ; 

bool_t
xdrrec_endofrecord(XDR *xdrs, bool_t sendnow)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	u_long len;  /* fragment length */

	if (sendnow || rstrm->frag_sent ||
		((u_long)rstrm->out_finger + sizeof(u_int32_t) >=
		(u_long)rstrm->out_boundry)) {
		rstrm->frag_sent = FALSE;
		return (flush_out(rstrm, TRUE));
	}
	len = (u_long)(rstrm->out_finger) - (u_long)(rstrm->frag_header) -
	   sizeof(u_int32_t);
	*(rstrm->frag_header) = htonl((u_int32_t)len | LAST_FRAG);
	rstrm->frag_header = (u_int32_t *)(void *)rstrm->out_finger;
	rstrm->out_finger += sizeof(u_int32_t);
	return (TRUE);
}