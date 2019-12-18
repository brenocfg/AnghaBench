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
struct savefpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpu_save_area_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct savefpu*) ; 

void
fpu_save_area_free(struct savefpu *fsa)
{

	uma_zfree(fpu_save_area_zone, fsa);
}