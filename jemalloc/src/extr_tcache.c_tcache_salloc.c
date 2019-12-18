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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 size_t arena_salloc (int /*<<< orphan*/ *,void const*) ; 

size_t
tcache_salloc(tsdn_t *tsdn, const void *ptr) {
	return arena_salloc(tsdn, ptr);
}