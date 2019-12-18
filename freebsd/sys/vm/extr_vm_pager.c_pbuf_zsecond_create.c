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
typedef  int /*<<< orphan*/  uma_zone_t ;

/* Variables and functions */
 scalar_t__ nswbuf_max ; 
 int /*<<< orphan*/  pbuf_ctor ; 
 int /*<<< orphan*/  pbuf_dtor ; 
 int /*<<< orphan*/  pbuf_zone ; 
 int /*<<< orphan*/  uma_prealloc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ uma_zone_set_max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zsecond_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uma_zone_t
pbuf_zsecond_create(char *name, int max)
{
	uma_zone_t zone;

	zone = uma_zsecond_create(name, pbuf_ctor, pbuf_dtor, NULL, NULL,
	    pbuf_zone);
	/*
	 * uma_prealloc() rounds up to items per slab. If we would prealloc
	 * immediately on every pbuf_zsecond_create(), we may accumulate too
	 * much of difference between hard limit and prealloced items, which
	 * means wasted memory.
	 */
	if (nswbuf_max > 0)
		nswbuf_max += uma_zone_set_max(zone, max);
	else
		uma_prealloc(pbuf_zone, uma_zone_set_max(zone, max));

	return (zone);
}