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
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nlm_prog_4_freeresult(SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{

	(void) xdr_free(xdr_result, result);
	return (TRUE);
}