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
struct gmap {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmap_free (struct gmap*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void gmap_put(struct gmap *gmap)
{
	if (refcount_dec_and_test(&gmap->ref_count))
		gmap_free(gmap);
}