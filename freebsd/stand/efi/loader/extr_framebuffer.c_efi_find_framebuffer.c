#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct efi_fb {int dummy; } ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ (* LocateProtocol ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  Info; } ;
struct TYPE_4__ {TYPE_2__* Mode; } ;
typedef  int /*<<< orphan*/  EFI_UGA_DRAW_PROTOCOL ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_1__ EFI_GRAPHICS_OUTPUT ;

/* Variables and functions */
 TYPE_3__* BS ; 
 scalar_t__ EFI_SUCCESS ; 
 int efifb_from_gop (struct efi_fb*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int efifb_from_uga (struct efi_fb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gop_guid ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uga_guid ; 

int
efi_find_framebuffer(struct efi_fb *efifb)
{
	EFI_GRAPHICS_OUTPUT *gop;
	EFI_UGA_DRAW_PROTOCOL *uga;
	EFI_STATUS status;

	status = BS->LocateProtocol(&gop_guid, NULL, (VOID **)&gop);
	if (status == EFI_SUCCESS)
		return (efifb_from_gop(efifb, gop->Mode, gop->Mode->Info));

	status = BS->LocateProtocol(&uga_guid, NULL, (VOID **)&uga);
	if (status == EFI_SUCCESS)
		return (efifb_from_uga(efifb, uga));

	return (1);
}