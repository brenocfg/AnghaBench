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
struct ck_rhs_map {int /*<<< orphan*/  capacity; } ;
struct ck_rhs {struct ck_rhs_map* map; } ;

/* Variables and functions */
 int ck_rhs_reset_size (struct ck_rhs*,int /*<<< orphan*/ ) ; 

bool
ck_rhs_reset(struct ck_rhs *hs)
{
	struct ck_rhs_map *previous;

	previous = hs->map;
	return ck_rhs_reset_size(hs, previous->capacity);
}