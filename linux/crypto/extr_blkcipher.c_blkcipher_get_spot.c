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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/ * max (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u8 *blkcipher_get_spot(u8 *start, unsigned int len)
{
	u8 *end_page = (u8 *)(((unsigned long)(start + len - 1)) & PAGE_MASK);
	return max(start, end_page);
}