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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int* window_buf; size_t window_mask; int solid_offset; int /*<<< orphan*/  filtered_buf; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct filter_info {int block_start; int block_length; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  circular_memcpy (int /*<<< orphan*/ ,int*,size_t,int,int) ; 
 int read_filter_data (struct rar5*,int) ; 
 int /*<<< orphan*/  write_filter_data (struct rar5*,int,int) ; 

__attribute__((used)) static int run_e8e9_filter(struct rar5* rar, struct filter_info* flt,
		int extended)
{
	const uint32_t file_size = 0x1000000;
	ssize_t i;

	circular_memcpy(rar->cstate.filtered_buf,
	    rar->cstate.window_buf, rar->cstate.window_mask,
	    rar->cstate.solid_offset + flt->block_start,
	    rar->cstate.solid_offset + flt->block_start + flt->block_length);

	for(i = 0; i < flt->block_length - 4;) {
		uint8_t b = rar->cstate.window_buf[
		    (rar->cstate.solid_offset + flt->block_start +
		    i++) & rar->cstate.window_mask];

		/*
		 * 0xE8 = x86's call <relative_addr_uint32> (function call)
		 * 0xE9 = x86's jmp <relative_addr_uint32> (unconditional jump)
		 */
		if(b == 0xE8 || (extended && b == 0xE9)) {

			uint32_t addr;
			uint32_t offset = (i + flt->block_start) % file_size;

			addr = read_filter_data(rar,
			    (uint32_t)(rar->cstate.solid_offset +
			    flt->block_start + i) & rar->cstate.window_mask);

			if(addr & 0x80000000) {
				if(((addr + offset) & 0x80000000) == 0) {
					write_filter_data(rar, (uint32_t)i,
					    addr + file_size);
				}
			} else {
				if((addr - file_size) & 0x80000000) {
					uint32_t naddr = addr - offset;
					write_filter_data(rar, (uint32_t)i,
					    naddr);
				}
			}

			i += 4;
		}
	}

	return ARCHIVE_OK;
}