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
struct csum {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bswap32 (int /*<<< orphan*/ ) ; 

void
ffs_csum_swap(struct csum *o, struct csum *n, int size)
{
	size_t i;
	u_int32_t *oint, *nint;

	oint = (u_int32_t*)o;
	nint = (u_int32_t*)n;

	for (i = 0; i < size / sizeof(u_int32_t); i++)
		nint[i] = bswap32(oint[i]);
}