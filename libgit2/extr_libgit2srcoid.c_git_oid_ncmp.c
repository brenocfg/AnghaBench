#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* id; } ;
typedef  TYPE_1__ git_oid ;

/* Variables and functions */
 size_t GIT_OID_HEXSZ ; 

int git_oid_ncmp(const git_oid *oid_a, const git_oid *oid_b, size_t len)
{
	const unsigned char *a = oid_a->id;
	const unsigned char *b = oid_b->id;

	if (len > GIT_OID_HEXSZ)
		len = GIT_OID_HEXSZ;

	while (len > 1) {
		if (*a != *b)
			return 1;
		a++;
		b++;
		len -= 2;
	};

	if (len)
		if ((*a ^ *b) & 0xf0)
			return 1;

	return 0;
}