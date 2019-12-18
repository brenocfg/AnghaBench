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

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int cmp_int(const void *_a, const void *_b, void *payload)
{
	int a = *(const int *)_a, b = *(const int *)_b;
	GIT_UNUSED(payload);
	return (a < b) ? -1 : (a > b) ? +1 : 0;
}