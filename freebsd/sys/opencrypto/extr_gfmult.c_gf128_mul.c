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
struct gf128table {int dummy; } ;
struct gf128 {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 struct gf128 MAKE_GF128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gf128 gfmultword (int /*<<< orphan*/ ,struct gf128,struct gf128table*) ; 

struct gf128
gf128_mul(struct gf128 v, struct gf128table *tbl)
{
	struct gf128 ret;

	ret = MAKE_GF128(0, 0);

	ret = gfmultword(v.v[1], ret, tbl);
	ret = gfmultword(v.v[0], ret, tbl);

	return ret;
}