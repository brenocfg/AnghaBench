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
 int /*<<< orphan*/  RUSERSPROC_NUM ; 
 int /*<<< orphan*/  RUSERSPROG ; 
 int /*<<< orphan*/  RUSERSVERS_ORIG ; 
 scalar_t__ callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_u_long ; 
 scalar_t__ xdr_void ; 

int
rnusers(char *host)
{
	int nusers;

	if (callrpc(host, RUSERSPROG, RUSERSVERS_ORIG, RUSERSPROC_NUM,
			(xdrproc_t)xdr_void, (char *) NULL,
			(xdrproc_t)xdr_u_long, (char *) &nusers) != 0)
		return (-1);
	else
		return (nusers);
}