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
struct netmap_priv_d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 int /*<<< orphan*/  netmap_priv_delete (struct netmap_priv_d*) ; 

void
netmap_dtor(void *data)
{
	struct netmap_priv_d *priv = data;

	NMG_LOCK();
	netmap_priv_delete(priv);
	NMG_UNLOCK();
}