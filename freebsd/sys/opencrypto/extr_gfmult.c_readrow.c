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
typedef  int uint64_t ;
struct gf128table {int* b; int* d; scalar_t__* c; scalar_t__* a; } ;
struct gf128 {int* v; } ;

/* Variables and functions */

__attribute__((used)) static inline struct gf128
readrow(struct gf128table *tbl, unsigned bits)
{
	struct gf128 r;

	bits = bits % 16;

	r.v[0] = ((uint64_t)tbl->a[bits] << 32) | tbl->b[bits];
	r.v[1] = ((uint64_t)tbl->c[bits] << 32) | tbl->d[bits];

	return r;
}