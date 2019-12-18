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
struct TYPE_2__ {unsigned long n_entries; } ;

/* Variables and functions */

unsigned long
ck_hs_count(struct ck_hs *hs)
{

	return hs->map->n_entries;
}