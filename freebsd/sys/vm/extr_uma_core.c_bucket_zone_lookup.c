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
struct uma_bucket_zone {int ubz_entries; } ;

/* Variables and functions */
 struct uma_bucket_zone* bucket_zones ; 

__attribute__((used)) static struct uma_bucket_zone *
bucket_zone_lookup(int entries)
{
	struct uma_bucket_zone *ubz;

	for (ubz = &bucket_zones[0]; ubz->ubz_entries != 0; ubz++)
		if (ubz->ubz_entries >= entries)
			return (ubz);
	ubz--;
	return (ubz);
}