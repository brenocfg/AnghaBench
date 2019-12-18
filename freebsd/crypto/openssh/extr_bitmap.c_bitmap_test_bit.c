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
typedef  size_t u_int ;
struct bitmap {scalar_t__ top; scalar_t__ len; size_t* d; } ;

/* Variables and functions */
 size_t BITMAP_BITS ; 
 size_t BITMAP_WMASK ; 

int
bitmap_test_bit(struct bitmap *b, u_int n)
{
	if (b->top >= b->len)
		return 0; /* invalid */
	if (b->len == 0 || (n / BITMAP_BITS) > b->top)
		return 0;
	return (b->d[n / BITMAP_BITS] >> (n & BITMAP_WMASK)) & 1;
}