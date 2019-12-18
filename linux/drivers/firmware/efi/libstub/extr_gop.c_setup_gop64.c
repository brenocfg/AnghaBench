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
typedef  int u64 ;
typedef  int u32 ;
typedef  void* u16 ;
struct screen_info {int lfb_height; int lfb_base; int ext_lfb_base; int pages; int lfb_size; int lfb_linelength; int /*<<< orphan*/  capabilities; void* lfb_width; int /*<<< orphan*/  orig_video_isVGA; } ;
struct efi_pixel_bitmask {int dummy; } ;
struct efi_graphics_output_protocol_64 {int dummy; } ;
struct efi_graphics_output_mode_info {int pixel_format; int pixels_per_scan_line; struct efi_pixel_bitmask pixel_information; void* vertical_resolution; void* horizontal_resolution; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_status_t ;
typedef  int /*<<< orphan*/  efi_handle_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_CONSOLE_OUT_DEVICE_GUID ; 
 int /*<<< orphan*/  EFI_NOT_FOUND ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int PIXEL_BLT_ONLY ; 
 int /*<<< orphan*/  VIDEO_CAPABILITY_64BIT_BASE ; 
 int /*<<< orphan*/  VIDEO_CAPABILITY_SKIP_QUIRKS ; 
 int /*<<< orphan*/  VIDEO_TYPE_EFI ; 
 int /*<<< orphan*/  __gop_query64 (int /*<<< orphan*/ *,struct efi_graphics_output_protocol_64*,struct efi_graphics_output_mode_info**,unsigned long*,int*) ; 
 int /*<<< orphan*/  efi_call_early (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  handle_protocol ; 
 int /*<<< orphan*/  setup_pixel_info (struct screen_info*,int,struct efi_pixel_bitmask,int) ; 

__attribute__((used)) static efi_status_t
setup_gop64(efi_system_table_t *sys_table_arg, struct screen_info *si,
	    efi_guid_t *proto, unsigned long size, void **gop_handle)
{
	struct efi_graphics_output_protocol_64 *gop64, *first_gop;
	unsigned long nr_gops;
	u16 width, height;
	u32 pixels_per_scan_line;
	u32 ext_lfb_base;
	u64 fb_base;
	struct efi_pixel_bitmask pixel_info;
	int pixel_format;
	efi_status_t status = EFI_NOT_FOUND;
	u64 *handles = (u64 *)(unsigned long)gop_handle;
	int i;

	first_gop = NULL;
	gop64 = NULL;

	nr_gops = size / sizeof(u64);
	for (i = 0; i < nr_gops; i++) {
		struct efi_graphics_output_mode_info *info = NULL;
		efi_guid_t conout_proto = EFI_CONSOLE_OUT_DEVICE_GUID;
		bool conout_found = false;
		void *dummy = NULL;
		efi_handle_t h = (efi_handle_t)(unsigned long)handles[i];
		u64 current_fb_base;

		status = efi_call_early(handle_protocol, h,
					proto, (void **)&gop64);
		if (status != EFI_SUCCESS)
			continue;

		status = efi_call_early(handle_protocol, h,
					&conout_proto, &dummy);
		if (status == EFI_SUCCESS)
			conout_found = true;

		status = __gop_query64(sys_table_arg, gop64, &info, &size,
				       &current_fb_base);
		if (status == EFI_SUCCESS && (!first_gop || conout_found) &&
		    info->pixel_format != PIXEL_BLT_ONLY) {
			/*
			 * Systems that use the UEFI Console Splitter may
			 * provide multiple GOP devices, not all of which are
			 * backed by real hardware. The workaround is to search
			 * for a GOP implementing the ConOut protocol, and if
			 * one isn't found, to just fall back to the first GOP.
			 */
			width = info->horizontal_resolution;
			height = info->vertical_resolution;
			pixel_format = info->pixel_format;
			pixel_info = info->pixel_information;
			pixels_per_scan_line = info->pixels_per_scan_line;
			fb_base = current_fb_base;

			/*
			 * Once we've found a GOP supporting ConOut,
			 * don't bother looking any further.
			 */
			first_gop = gop64;
			if (conout_found)
				break;
		}
	}

	/* Did we find any GOPs? */
	if (!first_gop)
		goto out;

	/* EFI framebuffer */
	si->orig_video_isVGA = VIDEO_TYPE_EFI;

	si->lfb_width = width;
	si->lfb_height = height;
	si->lfb_base = fb_base;

	ext_lfb_base = (u64)(unsigned long)fb_base >> 32;
	if (ext_lfb_base) {
		si->capabilities |= VIDEO_CAPABILITY_64BIT_BASE;
		si->ext_lfb_base = ext_lfb_base;
	}

	si->pages = 1;

	setup_pixel_info(si, pixels_per_scan_line, pixel_info, pixel_format);

	si->lfb_size = si->lfb_linelength * si->lfb_height;

	si->capabilities |= VIDEO_CAPABILITY_SKIP_QUIRKS;
out:
	return status;
}