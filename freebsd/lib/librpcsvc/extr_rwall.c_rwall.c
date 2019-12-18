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
 int /*<<< orphan*/  WALLPROC_WALL ; 
 int /*<<< orphan*/  WALLPROG ; 
 int /*<<< orphan*/  WALLVERS ; 
 int callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_void ; 
 scalar_t__ xdr_wrapstring ; 

int
rwall(char *host, char *msg)
{
	return (callrpc(host, WALLPROG, WALLVERS, WALLPROC_WALL,
			(xdrproc_t)xdr_wrapstring, (char *) &msg,
			(xdrproc_t)xdr_void, (char *) NULL));
}