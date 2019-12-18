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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct pmaplist {int dummy; } ;
typedef  struct pmaplist* rpcblist_ptr ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  PMAPFILE ; 
 int /*<<< orphan*/  RPCBFILE ; 
 int TRUE ; 
 struct pmaplist* list_pml ; 
 struct pmaplist* list_rbl ; 
 int read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmaplist**) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_pmaplist_ptr ; 
 scalar_t__ xdr_rpcblist_ptr ; 

void
read_warmstart(void)
{
	rpcblist_ptr tmp_rpcbl = NULL;
#ifdef PORTMAP
	struct pmaplist *tmp_pmapl = NULL;
#endif
	int ok1, ok2 = TRUE;

	ok1 = read_struct(RPCBFILE, (xdrproc_t)xdr_rpcblist_ptr, &tmp_rpcbl);
	if (ok1 == FALSE)
		return;
#ifdef PORTMAP
	ok2 = read_struct(PMAPFILE, (xdrproc_t)xdr_pmaplist_ptr, &tmp_pmapl);
#endif
	if (ok2 == FALSE) {
		xdr_free((xdrproc_t) xdr_rpcblist_ptr, (char *)&tmp_rpcbl);
		return;
	}
	xdr_free((xdrproc_t) xdr_rpcblist_ptr, (char *)&list_rbl);
	list_rbl = tmp_rpcbl;
#ifdef PORTMAP
	xdr_free((xdrproc_t) xdr_pmaplist_ptr, (char *)&list_pml);
	list_pml = tmp_pmapl;
#endif
}