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
struct bcache {struct bcache* bcache_data; struct bcache* bcache_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct bcache*) ; 

__attribute__((used)) static void
bcache_free_instance(struct bcache *bc)
{
    if (bc != NULL) {
	free(bc->bcache_ctl);
	free(bc->bcache_data);
	free(bc);
    }
}