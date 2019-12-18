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
struct mlx5_crspace_regmap {scalar_t__ cnt; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
mlx5_fwdump_getsize(const struct mlx5_crspace_regmap *rege)
{
	const struct mlx5_crspace_regmap *r;
	unsigned sz;

	for (sz = 0, r = rege; r->cnt != 0; r++)
		sz += r->cnt;
	return (sz);
}