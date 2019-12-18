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
struct TYPE_4__ {int xc_num_avail; int /*<<< orphan*/  xc_is_last_record; } ;
typedef  TYPE_1__ xdr_bytesrec ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int x_handy; char* x_private; } ;
typedef  TYPE_2__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int RNDUP (int) ; 
 int /*<<< orphan*/  TRUE ; 
#define  XDR_GET_BYTES_AVAIL 130 
#define  XDR_PEEK 129 
#define  XDR_SKIPBYTES 128 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
xdrmem_control(XDR *xdrs, int request, void *info)
{
	xdr_bytesrec *xptr;
	int32_t *l;
	int len;

	switch (request) {

	case XDR_GET_BYTES_AVAIL:
		xptr = (xdr_bytesrec *)info;
		xptr->xc_is_last_record = TRUE;
		xptr->xc_num_avail = xdrs->x_handy;
		return (TRUE);

	case XDR_PEEK:
		/*
		 * Return the next 4 byte unit in the XDR stream.
		 */
		if (xdrs->x_handy < sizeof (int32_t))
			return (FALSE);
		l = (int32_t *)info;
		*l = (int32_t)ntohl((uint32_t)
		    (*((int32_t *)(xdrs->x_private))));
		return (TRUE);

	case XDR_SKIPBYTES:
		/*
		 * Skip the next N bytes in the XDR stream.
		 */
		l = (int32_t *)info;
		len = RNDUP((int)(*l));
		if (xdrs->x_handy < len)
			return (FALSE);
		xdrs->x_handy -= len;
		xdrs->x_private = (char *)xdrs->x_private + len;
		return (TRUE);

	}
	return (FALSE);
}