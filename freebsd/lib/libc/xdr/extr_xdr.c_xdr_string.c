#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 int /*<<< orphan*/  free (char*) ; 
 char* mem_alloc (scalar_t__) ; 
 int /*<<< orphan*/  mem_free (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xdr_opaque (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_u_int (TYPE_1__*,scalar_t__*) ; 

bool_t
xdr_string(XDR *xdrs, char **cpp, u_int maxsize)
{
	char *sp = *cpp;  /* sp is the actual string pointer */
	u_int size;
	u_int nodesize;
	bool_t ret, allocated = FALSE;

	/*
	 * first deal with the length since xdr strings are counted-strings
	 */
	switch (xdrs->x_op) {
	case XDR_FREE:
		if (sp == NULL) {
			return(TRUE);	/* already free */
		}
		/* FALLTHROUGH */
	case XDR_ENCODE:
		size = strlen(sp);
		break;
	case XDR_DECODE:
		break;
	}
	if (! xdr_u_int(xdrs, &size)) {
		return (FALSE);
	}
	if (size > maxsize) {
		return (FALSE);
	}
	nodesize = size + 1;

	/*
	 * now deal with the actual bytes
	 */
	switch (xdrs->x_op) {

	case XDR_DECODE:
		if (nodesize == 0) {
			return (TRUE);
		}
		if (sp == NULL) {
			*cpp = sp = mem_alloc(nodesize);
			allocated = TRUE;
		}
		if (sp == NULL) {
			warnx("xdr_string: out of memory");
			return (FALSE);
		}
		sp[size] = 0;
		/* FALLTHROUGH */

	case XDR_ENCODE:
		ret = xdr_opaque(xdrs, sp, size);
		if ((xdrs->x_op == XDR_DECODE) && (ret == FALSE)) {
			if (allocated == TRUE) {
				free(sp);
				*cpp = NULL;
			}
		}
		return (ret);

	case XDR_FREE:
		mem_free(sp, nodesize);
		*cpp = NULL;
		return (TRUE);
	}
	/* NOTREACHED */
	return (FALSE);
}