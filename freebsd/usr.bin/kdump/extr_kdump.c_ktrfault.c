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
typedef  int /*<<< orphan*/  uintmax_t ;
struct ktr_fault {int /*<<< orphan*/  type; scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_mask_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sysdecode_vmprot ; 

void
ktrfault(struct ktr_fault *ktr)
{

	printf("0x%jx ", (uintmax_t)ktr->vaddr);
	print_mask_arg(sysdecode_vmprot, ktr->type);
	printf("\n");
}