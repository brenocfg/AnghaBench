#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,char*) ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*) ; 

bool_t
xdr_vector(XDR *xdrs, char *basep, u_int nelem, u_int elemsize, xdrproc_t xdr_elem)
{
	u_int i;
	char *elptr;

	elptr = basep;
	for (i = 0; i < nelem; i++) {
		if (!(*xdr_elem)(xdrs, elptr)) {
			return(FALSE);
		}
		elptr += elemsize;
	}
	return(TRUE);	
}