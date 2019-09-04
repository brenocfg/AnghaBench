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
typedef  int /*<<< orphan*/  uint32_t ;
struct island_bitmap {int* bits; } ;

/* Variables and functions */
 size_t ISLAND_BITMAP_BLOCK (int /*<<< orphan*/ ) ; 
 int ISLAND_BITMAP_MASK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int island_bitmap_get(struct island_bitmap *self, uint32_t i)
{
	return (self->bits[ISLAND_BITMAP_BLOCK(i)] & ISLAND_BITMAP_MASK(i)) != 0;
}