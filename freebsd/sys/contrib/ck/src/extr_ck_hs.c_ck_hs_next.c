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
struct ck_hs_iterator {int dummy; } ;
struct ck_hs {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int _ck_hs_next (struct ck_hs*,int /*<<< orphan*/ ,struct ck_hs_iterator*,void**) ; 

bool
ck_hs_next(struct ck_hs *hs, struct ck_hs_iterator *i, void **key)
{
	return _ck_hs_next(hs, hs->map, i, key);
}