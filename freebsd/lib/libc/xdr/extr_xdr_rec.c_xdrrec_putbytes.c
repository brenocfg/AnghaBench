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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_6__ {scalar_t__ out_boundry; scalar_t__ out_finger; int /*<<< orphan*/  frag_sent; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  flush_out (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static bool_t
xdrrec_putbytes(XDR *xdrs, const char *addr, u_int len)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	size_t current;

	while (len > 0) {
		current = (size_t)((u_long)rstrm->out_boundry -
		    (u_long)rstrm->out_finger);
		current = (len < current) ? len : current;
		memmove(rstrm->out_finger, addr, current);
		rstrm->out_finger += current;
		addr += current;
		len -= current;
		if (rstrm->out_finger == rstrm->out_boundry) {
			rstrm->frag_sent = TRUE;
			if (! flush_out(rstrm, FALSE))
				return (FALSE);
		}
	}
	return (TRUE);
}