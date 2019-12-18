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
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  csum_partial (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

__wsum
csum_partial_copy_nocheck(const void *src, void *dst, int len, __wsum sum)
{
	memcpy(dst, src, len);
	return csum_partial(dst, len, sum);
}