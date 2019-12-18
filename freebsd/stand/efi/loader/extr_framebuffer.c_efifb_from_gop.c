#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct efi_fb {int /*<<< orphan*/  fb_stride; int /*<<< orphan*/  fb_width; int /*<<< orphan*/  fb_height; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  PixelInformation; int /*<<< orphan*/  PixelFormat; int /*<<< orphan*/  PixelsPerScanLine; int /*<<< orphan*/  HorizontalResolution; int /*<<< orphan*/  VerticalResolution; } ;
struct TYPE_5__ {int /*<<< orphan*/  FrameBufferSize; int /*<<< orphan*/  FrameBufferBase; } ;
typedef  TYPE_1__ EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE ;
typedef  TYPE_2__ EFI_GRAPHICS_OUTPUT_MODE_INFORMATION ;

/* Variables and functions */
 int efifb_mask_from_pixfmt (struct efi_fb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
efifb_from_gop(struct efi_fb *efifb, EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *mode,
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info)
{
	int result;

	efifb->fb_addr = mode->FrameBufferBase;
	efifb->fb_size = mode->FrameBufferSize;
	efifb->fb_height = info->VerticalResolution;
	efifb->fb_width = info->HorizontalResolution;
	efifb->fb_stride = info->PixelsPerScanLine;
	result = efifb_mask_from_pixfmt(efifb, info->PixelFormat,
	    &info->PixelInformation);
	return (result);
}