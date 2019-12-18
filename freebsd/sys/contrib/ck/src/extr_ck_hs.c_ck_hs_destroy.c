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
struct ck_hs {int /*<<< orphan*/  map; int /*<<< orphan*/  m; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_hs_map_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ck_hs_destroy(struct ck_hs *hs)
{

	ck_hs_map_destroy(hs->m, hs->map, false);
	return;
}