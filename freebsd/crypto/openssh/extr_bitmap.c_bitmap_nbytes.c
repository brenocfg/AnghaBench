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
struct bitmap {int dummy; } ;

/* Variables and functions */
 int bitmap_nbits (struct bitmap*) ; 

size_t
bitmap_nbytes(struct bitmap *b)
{
	return (bitmap_nbits(b) + 7) / 8;
}