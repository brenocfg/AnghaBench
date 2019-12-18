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
struct _malloc_zone_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zone_free (struct _malloc_zone_t*,void*) ; 

__attribute__((used)) static void
zone_batch_free(struct _malloc_zone_t *zone, void **to_be_freed,
    unsigned num_to_be_freed) {
	unsigned i;

	for (i = 0; i < num_to_be_freed; i++) {
		zone_free(zone, to_be_freed[i]);
		to_be_freed[i] = NULL;
	}
}