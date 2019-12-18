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
struct ondisk_cache_entry {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ align_padding_size (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t estimate_cache_size(size_t ondisk_size, unsigned int entries)
{
	long per_entry = sizeof(struct cache_entry) - sizeof(struct ondisk_cache_entry);

	/*
	 * Account for potential alignment differences.
	 */
	per_entry += align_padding_size(per_entry, 0);
	return ondisk_size + entries * per_entry;
}