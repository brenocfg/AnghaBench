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
typedef  int uint32_t ;
struct TYPE_2__ {uintptr_t sched_nr; } ;
struct dn_schk {TYPE_1__ sch; } ;

/* Variables and functions */
 int DNHT_KEY_IS_OBJ ; 

__attribute__((used)) static uint32_t
schk_hash(uintptr_t key, int flags, void *_arg)
{
	uint32_t i = !(flags & DNHT_KEY_IS_OBJ) ? key :
		((struct dn_schk *)key)->sch.sched_nr;
	return ( (i>>8)^(i>>4)^i );
}