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
typedef  int /*<<< orphan*/  utmpidlearr ;

/* Variables and functions */
 int /*<<< orphan*/  RUSERSPROC_NAMES ; 
 int /*<<< orphan*/  RUSERSPROG ; 
 int /*<<< orphan*/  RUSERSVERS_IDLE ; 
 int callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_utmpidlearr ; 
 scalar_t__ xdr_void ; 

int
rusers(char *host, utmpidlearr *up)
{
	return (callrpc(host, RUSERSPROG, RUSERSVERS_IDLE, RUSERSPROC_NAMES,
			(xdrproc_t)xdr_void, (char *) NULL,
			(xdrproc_t)xdr_utmpidlearr, (char *) up));
}