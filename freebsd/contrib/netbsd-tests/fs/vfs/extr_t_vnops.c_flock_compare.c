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
struct flock {int l_start; } ;

/* Variables and functions */

__attribute__((used)) static int
flock_compare(const void *p, const void *q)
{
	int a = ((const struct flock *)p)->l_start;
	int b = ((const struct flock *)q)->l_start;
	return a < b ? -1 : (a > b ? 1 : 0);
}