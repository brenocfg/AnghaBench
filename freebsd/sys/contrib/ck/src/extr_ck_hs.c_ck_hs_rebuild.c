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
struct ck_hs {TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  capacity; } ;

/* Variables and functions */
 int ck_hs_grow (struct ck_hs*,int /*<<< orphan*/ ) ; 

bool
ck_hs_rebuild(struct ck_hs *hs)
{

	return ck_hs_grow(hs, hs->map->capacity);
}