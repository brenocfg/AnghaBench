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
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/  je_posix_memalign (void**,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void *
zone_valloc(malloc_zone_t *zone, size_t size) {
	void *ret = NULL; /* Assignment avoids useless compiler warning. */

	je_posix_memalign(&ret, PAGE, size);

	return ret;
}