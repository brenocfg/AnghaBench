#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snapshot_record {char* start; } ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int cmp_packed_ref_records(const void *v1, const void *v2)
{
	const struct snapshot_record *e1 = v1, *e2 = v2;
	const char *r1 = e1->start + the_hash_algo->hexsz + 1;
	const char *r2 = e2->start + the_hash_algo->hexsz + 1;

	while (1) {
		if (*r1 == '\n')
			return *r2 == '\n' ? 0 : -1;
		if (*r1 != *r2) {
			if (*r2 == '\n')
				return 1;
			else
				return (unsigned char)*r1 < (unsigned char)*r2 ? -1 : +1;
		}
		r1++;
		r2++;
	}
}