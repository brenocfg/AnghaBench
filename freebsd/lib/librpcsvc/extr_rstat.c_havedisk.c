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
 int /*<<< orphan*/  RSTATPROC_HAVEDISK ; 
 int /*<<< orphan*/  RSTATPROG ; 
 int /*<<< orphan*/  RSTATVERS_SWTCH ; 
 scalar_t__ callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_long ; 
 scalar_t__ xdr_void ; 

int
havedisk(char *host)
{
	long have;
	
	if (callrpc(host, RSTATPROG, RSTATVERS_SWTCH, RSTATPROC_HAVEDISK,
			(xdrproc_t)xdr_void, (char *) NULL,
			(xdrproc_t)xdr_long, (char *) &have) != 0)
		return (-1);
	else
		return (have);
}