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
typedef  int /*<<< orphan*/  malloc_zone_t ;

/* Variables and functions */
 scalar_t__ ivsalloc (int /*<<< orphan*/ ,void*) ; 
 void* je_realloc (void*,size_t) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  tsdn_fetch () ; 

__attribute__((used)) static void *
zone_realloc(malloc_zone_t *zone, void *ptr, size_t size) {
	if (ivsalloc(tsdn_fetch(), ptr) != 0) {
		return je_realloc(ptr, size);
	}

	return realloc(ptr, size);
}