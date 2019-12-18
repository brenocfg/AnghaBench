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
struct ewah_bitmap {int dummy; } ;

/* Variables and functions */
 struct ewah_bitmap** bitmap_pool ; 
 int bitmap_pool_size ; 
 struct ewah_bitmap* ewah_new () ; 

struct ewah_bitmap *ewah_pool_new(void)
{
	if (bitmap_pool_size)
		return bitmap_pool[--bitmap_pool_size];

	return ewah_new();
}