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

/* Variables and functions */
 int /*<<< orphan*/  PMAPFILE ; 
 int /*<<< orphan*/  RPCBFILE ; 
 int /*<<< orphan*/  list_pml ; 
 int /*<<< orphan*/  list_rbl ; 
 int /*<<< orphan*/  write_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_pmaplist_ptr ; 
 scalar_t__ xdr_rpcblist_ptr ; 

void
write_warmstart(void)
{
	(void) write_struct(RPCBFILE, (xdrproc_t)xdr_rpcblist_ptr, &list_rbl);
#ifdef PORTMAP
	(void) write_struct(PMAPFILE, (xdrproc_t)xdr_pmaplist_ptr, &list_pml);
#endif

}