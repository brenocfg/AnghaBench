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
 int BIT_MODEL_INIT ; 

__attribute__((used)) static void
lz_bm_init(int *a, size_t l)
{
	for (size_t i = 0; i < l; i++)
		a[i] = BIT_MODEL_INIT;
}