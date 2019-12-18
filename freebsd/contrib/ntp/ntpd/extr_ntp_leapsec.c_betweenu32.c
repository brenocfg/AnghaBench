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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int/*BOOL*/
betweenu32(
	uint32_t lo,
	uint32_t x,
	uint32_t hi)
{
	int rc;

	if (lo <= hi)
		rc = (lo <= x) && (x < hi);
	else
		rc = (lo <= x) || (x < hi);
	return rc;
}