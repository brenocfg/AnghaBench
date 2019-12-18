#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* Exit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* FreePages ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 TYPE_1__* BS ; 
 int /*<<< orphan*/  EFI_SIZE_TO_PAGES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IH ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  heapsize ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
efi_exit(EFI_STATUS exit_code)
{

	BS->FreePages(heap, EFI_SIZE_TO_PAGES(heapsize));
	BS->Exit(IH, exit_code, 0, NULL);
}