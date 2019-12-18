#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  phandle ;
struct TYPE_2__ {int (* no_getprop ) (int /*<<< orphan*/ ,char const*,char*) ;} ;

/* Variables and functions */
 int prom_getproplen (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  prom_lock ; 
 TYPE_1__* prom_nodeops ; 
 int /*<<< orphan*/  restore_current () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,char*) ; 

int prom_getproperty(phandle node, const char *prop, char *buffer, int bufsize)
{
	int plen, ret;
	unsigned long flags;

	plen = prom_getproplen(node, prop);
	if((plen > bufsize) || (plen == 0) || (plen == -1))
		return -1;
	/* Ok, things seem all right. */
	spin_lock_irqsave(&prom_lock, flags);
	ret = prom_nodeops->no_getprop(node, prop, buffer);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	return ret;
}