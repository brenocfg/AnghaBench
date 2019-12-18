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
struct TYPE_6__ {int fbtbc; scalar_t__ in_finger; scalar_t__ in_boundry; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdrrec_getbytes (TYPE_1__*,char*,int) ; 

__attribute__((used)) static bool_t
xdrrec_getlong(XDR *xdrs, long *lp)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	int32_t *buflp = (int32_t *)(void *)(rstrm->in_finger);
	int32_t mylong;

	/* first try the inline, fast case */
	if ((rstrm->fbtbc >= sizeof(int32_t)) &&
		(((long)rstrm->in_boundry - (long)buflp) >= sizeof(int32_t))) {
		*lp = (long)ntohl((u_int32_t)(*buflp));
		rstrm->fbtbc -= sizeof(int32_t);
		rstrm->in_finger += sizeof(int32_t);
	} else {
		if (! xdrrec_getbytes(xdrs, (char *)(void *)&mylong,
		    sizeof(int32_t)))
			return (FALSE);
		*lp = (long)ntohl((u_int32_t)mylong);
	}
	return (TRUE);
}