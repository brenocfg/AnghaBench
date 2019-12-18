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
typedef  int /*<<< orphan*/  u64 ;
struct efi_graphics_output_protocol_mode_32 {int /*<<< orphan*/  frame_buffer_base; int /*<<< orphan*/  mode; } ;
struct efi_graphics_output_protocol_32 {unsigned long mode; scalar_t__ query_mode; } ;
struct efi_graphics_output_mode_info {int dummy; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  void* efi_graphics_output_protocol_query_mode ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ __efi_call_early (void*,void*,int /*<<< orphan*/ ,unsigned long*,struct efi_graphics_output_mode_info**) ; 

__attribute__((used)) static efi_status_t
__gop_query32(efi_system_table_t *sys_table_arg,
	      struct efi_graphics_output_protocol_32 *gop32,
	      struct efi_graphics_output_mode_info **info,
	      unsigned long *size, u64 *fb_base)
{
	struct efi_graphics_output_protocol_mode_32 *mode;
	efi_graphics_output_protocol_query_mode query_mode;
	efi_status_t status;
	unsigned long m;

	m = gop32->mode;
	mode = (struct efi_graphics_output_protocol_mode_32 *)m;
	query_mode = (void *)(unsigned long)gop32->query_mode;

	status = __efi_call_early(query_mode, (void *)gop32, mode->mode, size,
				  info);
	if (status != EFI_SUCCESS)
		return status;

	*fb_base = mode->frame_buffer_base;
	return status;
}