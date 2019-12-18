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
typedef  enum xprt_stat { ____Placeholder_xprt_stat } xprt_stat ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int XPRT_IDLE ; 

__attribute__((used)) static enum xprt_stat
svc_dg_stat(SVCXPRT *xprt)
{
	return (XPRT_IDLE);
}