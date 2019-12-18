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
struct tid_info {TYPE_1__* atid_tab; } ;
struct adapter {struct tid_info tids; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */

void *
lookup_atid(struct adapter *sc, int atid)
{
	struct tid_info *t = &sc->tids;

	return (t->atid_tab[atid].data);
}