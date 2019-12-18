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
typedef  int u_int32_t ;
struct agg_chinfo {int num; int phys; int base; scalar_t__ stereo; scalar_t__ qs16; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  APUREG_CURPTR ; 
 int /*<<< orphan*/  agg_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (int /*<<< orphan*/ ) ; 
 int wp_rdapu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
aggpch_getptr(kobj_t obj, void *data)
{
	struct agg_chinfo *ch = data;
	u_int32_t cp;

	agg_lock(ch->parent);
	cp = wp_rdapu(ch->parent, (ch->num << 1) | 32, APUREG_CURPTR);
	agg_unlock(ch->parent);

	return ch->qs16 && ch->stereo
		? (cp << 2) - ((0xffff << 2) & (ch->phys - ch->base))
		: (cp << 1) - ((0xffff << 1) & (ch->phys - ch->base));
}