#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amd64tss {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* FreePages ) (scalar_t__,int) ;} ;
struct TYPE_3__ {int rd_limit; } ;

/* Variables and functions */
 TYPE_2__* BS ; 
 int EFI_SIZE_TO_PAGES (int) ; 
 scalar_t__ exc_stack_pa ; 
 TYPE_1__ fw_idt ; 
 scalar_t__ ist ; 
 scalar_t__ lidt_pa ; 
 scalar_t__ loader_gdt_pa ; 
 scalar_t__ loader_tss ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int) ; 
 scalar_t__ tss_fw_seg ; 
 scalar_t__ tss_pa ; 

__attribute__((used)) static void
free_tables(void)
{

	if (lidt_pa != 0) {
		BS->FreePages(lidt_pa, EFI_SIZE_TO_PAGES(fw_idt.rd_limit));
		lidt_pa = 0;
	}
	if (exc_stack_pa != 0) {
		BS->FreePages(exc_stack_pa, 1);
		exc_stack_pa = 0;
	}
	if (tss_pa != 0 && tss_fw_seg == 0) {
		BS->FreePages(tss_pa, EFI_SIZE_TO_PAGES(sizeof(struct
		    amd64tss)));
		tss_pa = 0;
	}
	if (loader_gdt_pa != 0) {
		BS->FreePages(tss_pa, 2);
		loader_gdt_pa = 0;
	}
	ist = 0;
	loader_tss = 0;
}