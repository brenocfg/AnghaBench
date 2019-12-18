#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_6__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_7__ {scalar_t__ fbtbc; scalar_t__ last_frag; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_input_bytes (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  set_input_fragment (TYPE_2__*) ; 

__attribute__((used)) static bool_t  /* must manage buffers, fragments, and records */
xdrrec_getbytes(XDR *xdrs, char *addr, u_int len)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	int current;

	while (len > 0) {
		current = (int)rstrm->fbtbc;
		if (current == 0) {
			if (rstrm->last_frag)
				return (FALSE);
			if (! set_input_fragment(rstrm))
				return (FALSE);
			continue;
		}
		current = (len < current) ? len : current;
		if (! get_input_bytes(rstrm, addr, current))
			return (FALSE);
		addr += current; 
		rstrm->fbtbc -= current;
		len -= current;
	}
	return (TRUE);
}