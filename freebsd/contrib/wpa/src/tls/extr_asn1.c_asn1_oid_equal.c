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
struct asn1_oid {size_t len; scalar_t__* oid; } ;

/* Variables and functions */

int asn1_oid_equal(const struct asn1_oid *a, const struct asn1_oid *b)
{
	size_t i;

	if (a->len != b->len)
		return 0;

	for (i = 0; i < a->len; i++) {
		if (a->oid[i] != b->oid[i])
			return 0;
	}

	return 1;
}