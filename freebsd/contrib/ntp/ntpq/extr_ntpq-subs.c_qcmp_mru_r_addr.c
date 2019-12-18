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
 int qcmp_mru_addr (void const*,void const*) ; 

__attribute__((used)) static int
qcmp_mru_r_addr(
	const void *v1,
	const void *v2
	)
{
	return -qcmp_mru_addr(v1, v2);
}