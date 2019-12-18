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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct microcode_header_amd {int dummy; } ;

/* Variables and functions */
 size_t SECTION_HDR_SIZE ; 
 scalar_t__ UCODE_UCODE_TYPE ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static bool
__verify_patch_section(const u8 *buf, size_t buf_size, u32 *sh_psize, bool early)
{
	u32 p_type, p_size;
	const u32 *hdr;

	if (buf_size < SECTION_HDR_SIZE) {
		if (!early)
			pr_debug("Truncated patch section.\n");

		return false;
	}

	hdr = (const u32 *)buf;
	p_type = hdr[0];
	p_size = hdr[1];

	if (p_type != UCODE_UCODE_TYPE) {
		if (!early)
			pr_debug("Invalid type field (0x%x) in container file section header.\n",
				p_type);

		return false;
	}

	if (p_size < sizeof(struct microcode_header_amd)) {
		if (!early)
			pr_debug("Patch of size %u too short.\n", p_size);

		return false;
	}

	*sh_psize = p_size;

	return true;
}