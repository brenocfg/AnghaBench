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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_rchinfo {TYPE_1__* slot; struct sc_info* parent; } ;
struct sc_info {size_t currbank; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int /*<<< orphan*/  PgStart; } ;

/* Variables and functions */

__attribute__((used)) static u_int32_t
ds1rchan_getptr(kobj_t obj, void *data)
{
	struct sc_rchinfo *ch = data;
	struct sc_info *sc = ch->parent;

	return ch->slot[sc->currbank].PgStart;
}