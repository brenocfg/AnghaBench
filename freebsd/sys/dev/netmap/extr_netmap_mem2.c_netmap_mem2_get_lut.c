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
struct netmap_mem_d {TYPE_1__* pools; } ;
struct netmap_lut {int /*<<< orphan*/  objsize; int /*<<< orphan*/  objtotal; int /*<<< orphan*/  lut; int /*<<< orphan*/  plut; } ;
struct TYPE_2__ {int /*<<< orphan*/  _objsize; int /*<<< orphan*/  objtotal; int /*<<< orphan*/  lut; } ;

/* Variables and functions */
 size_t NETMAP_BUF_POOL ; 

__attribute__((used)) static int
netmap_mem2_get_lut(struct netmap_mem_d *nmd, struct netmap_lut *lut)
{
	lut->lut = nmd->pools[NETMAP_BUF_POOL].lut;
#ifdef __FreeBSD__
	lut->plut = lut->lut;
#endif
	lut->objtotal = nmd->pools[NETMAP_BUF_POOL].objtotal;
	lut->objsize = nmd->pools[NETMAP_BUF_POOL]._objsize;

	return 0;
}