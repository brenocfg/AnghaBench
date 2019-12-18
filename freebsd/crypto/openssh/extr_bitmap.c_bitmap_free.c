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
struct bitmap {struct bitmap* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_zero (struct bitmap*) ; 
 int /*<<< orphan*/  free (struct bitmap*) ; 

void
bitmap_free(struct bitmap *b)
{
	if (b != NULL && b->d != NULL) {
		bitmap_zero(b);
		free(b->d);
		b->d = NULL;
	}
	free(b);
}