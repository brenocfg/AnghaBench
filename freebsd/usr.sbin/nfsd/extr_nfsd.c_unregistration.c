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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NFS_PROGRAM ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
unregistration(void)
{
	if ((!rpcb_unset(NFS_PROGRAM, 2, NULL)) ||
	    (!rpcb_unset(NFS_PROGRAM, 3, NULL)))
		syslog(LOG_ERR, "rpcb_unset failed");
}