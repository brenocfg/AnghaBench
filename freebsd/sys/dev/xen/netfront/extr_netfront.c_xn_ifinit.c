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
struct netfront_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XN_LOCK (struct netfront_info*) ; 
 int /*<<< orphan*/  XN_UNLOCK (struct netfront_info*) ; 
 int /*<<< orphan*/  xn_ifinit_locked (struct netfront_info*) ; 

__attribute__((used)) static void
xn_ifinit(void *xsc)
{
	struct netfront_info *sc = xsc;

	XN_LOCK(sc);
	xn_ifinit_locked(sc);
	XN_UNLOCK(sc);
}