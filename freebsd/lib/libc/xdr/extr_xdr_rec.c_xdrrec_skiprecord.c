#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum xprt_stat { ____Placeholder_xprt_stat } xprt_stat ;
typedef  scalar_t__ bool_t ;
struct TYPE_7__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_8__ {scalar_t__ fbtbc; scalar_t__ in_finger; scalar_t__ in_boundry; scalar_t__ last_frag; scalar_t__ nonblock; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int XPRT_MOREREQS ; 
 scalar_t__ __xdrrec_getrec (TYPE_1__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  set_input_fragment (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_input_bytes (TYPE_2__*,scalar_t__) ; 

bool_t
xdrrec_skiprecord(XDR *xdrs)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	enum xprt_stat xstat;

	if (rstrm->nonblock) {
		if (__xdrrec_getrec(xdrs, &xstat, FALSE)) {
			rstrm->fbtbc = 0;
			return TRUE;
		}
		if (rstrm->in_finger == rstrm->in_boundry &&
		    xstat == XPRT_MOREREQS) {
			rstrm->fbtbc = 0;
			return TRUE;
		}
		return FALSE;
	}

	while (rstrm->fbtbc > 0 || (! rstrm->last_frag)) {
		if (! skip_input_bytes(rstrm, rstrm->fbtbc))
			return (FALSE);
		rstrm->fbtbc = 0;
		if ((! rstrm->last_frag) && (! set_input_fragment(rstrm)))
			return (FALSE);
	}
	rstrm->last_frag = FALSE;
	return (TRUE);
}