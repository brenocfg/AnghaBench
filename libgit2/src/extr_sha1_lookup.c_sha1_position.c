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

/* Variables and functions */
 int git_oid__hashcmp (unsigned char const*,unsigned char const*) ; 

int sha1_position(const void *table,
			size_t stride,
			unsigned lo, unsigned hi,
			const unsigned char *key)
{
	const unsigned char *base = table;

	while (lo < hi) {
		unsigned mi = (lo + hi) / 2;
		int cmp = git_oid__hashcmp(base + mi * stride, key);

		if (!cmp)
			return mi;

		if (cmp > 0)
			hi = mi;
		else
			lo = mi+1;
	}

	return -((int)lo)-1;
}