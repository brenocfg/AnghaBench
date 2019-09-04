#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int logmask; int /*<<< orphan*/ * writelog; } ;
typedef  TYPE_1__ ikcpcb ;

/* Variables and functions */

__attribute__((used)) static int ikcp_canlog(const ikcpcb *kcp, int mask)
{
	if ((mask & kcp->logmask) == 0 || kcp->writelog == NULL) return 0;
	return 1;
}