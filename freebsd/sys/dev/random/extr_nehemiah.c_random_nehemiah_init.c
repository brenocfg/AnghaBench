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
 int /*<<< orphan*/  FPU_KERN_NORMAL ; 
 int /*<<< orphan*/  fpu_ctx_save ; 
 int /*<<< orphan*/  fpu_kern_alloc_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
random_nehemiah_init(void)
{

	fpu_ctx_save = fpu_kern_alloc_ctx(FPU_KERN_NORMAL);
}