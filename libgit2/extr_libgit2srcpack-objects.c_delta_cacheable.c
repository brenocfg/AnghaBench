#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t max_delta_cache_size; size_t cache_max_small_delta_size; int /*<<< orphan*/  delta_cache_size; } ;
typedef  TYPE_1__ git_packbuilder ;

/* Variables and functions */
 scalar_t__ git__add_sizet_overflow (size_t*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int delta_cacheable(
	git_packbuilder *pb,
	size_t src_size,
	size_t trg_size,
	size_t delta_size)
{
	size_t new_size;

	if (git__add_sizet_overflow(&new_size, pb->delta_cache_size, delta_size))
		return 0;

	if (pb->max_delta_cache_size && new_size > pb->max_delta_cache_size)
		return 0;

	if (delta_size < pb->cache_max_small_delta_size)
		return 1;

	/* cache delta, if objects are large enough compared to delta size */
	if ((src_size >> 20) + (trg_size >> 21) > (delta_size >> 10))
		return 1;

	return 0;
}