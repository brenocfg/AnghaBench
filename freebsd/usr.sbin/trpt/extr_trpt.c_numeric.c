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
typedef  int caddr_t ;

/* Variables and functions */

__attribute__((used)) static int
numeric(const void *v1, const void *v2)
{
	const caddr_t *c1 = v1, *c2 = v2;

	return (*c1 - *c2);
}