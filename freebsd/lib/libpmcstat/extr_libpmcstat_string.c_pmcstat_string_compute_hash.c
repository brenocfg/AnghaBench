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
 unsigned int PMCSTAT_HASH_MASK ; 

int
pmcstat_string_compute_hash(const char *s)
{
	unsigned hash;

	for (hash = 2166136261; *s; s++)
		hash = (hash ^ *s) * 16777619;

	return (hash & PMCSTAT_HASH_MASK);
}