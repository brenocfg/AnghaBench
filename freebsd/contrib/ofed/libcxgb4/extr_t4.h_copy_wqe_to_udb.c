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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static void copy_wqe_to_udb(volatile u32 *udb_offset, void *wqe)
{
	u64 *src, *dst;
	int len16 = 4;

	src = (u64 *)wqe;
	dst = (u64 *)udb_offset;

	while (len16) {
		*dst++ = *src++;
		*dst++ = *src++;
		len16--;
	}
}