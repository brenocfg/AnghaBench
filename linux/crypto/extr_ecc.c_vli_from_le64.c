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

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le64 (int /*<<< orphan*/  const*) ; 

void vli_from_le64(u64 *dest, const void *src, unsigned int ndigits)
{
	int i;
	const u64 *from = src;

	for (i = 0; i < ndigits; i++)
		dest[i] = get_unaligned_le64(&from[i]);
}