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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_rchinfo {int /*<<< orphan*/  ptr; struct sc_info* parent; } ;
struct sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 

__attribute__((used)) static u_int32_t
m3_rchan_getptr(kobj_t kobj, void *chdata)
{
	struct sc_rchinfo *ch = chdata;
	struct sc_info *sc = ch->parent;
	u_int32_t ptr;

	M3_LOCK(sc);
	ptr = ch->ptr;
	M3_UNLOCK(sc);

	return (ptr);
}