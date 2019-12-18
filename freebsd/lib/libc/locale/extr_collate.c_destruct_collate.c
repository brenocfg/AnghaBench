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
struct xlocale_collate {scalar_t__ maplen; scalar_t__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  munmap (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
destruct_collate(void *t)
{
	struct xlocale_collate *table = t;
	if (table->map && (table->maplen > 0)) {
		(void) munmap(table->map, table->maplen);
	}
	free(t);
}