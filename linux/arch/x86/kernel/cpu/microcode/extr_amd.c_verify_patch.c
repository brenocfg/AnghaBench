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
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct microcode_header_amd {int processor_rev_id; int /*<<< orphan*/  patch_id; scalar_t__ sb_dev_id; scalar_t__ nb_dev_id; } ;

/* Variables and functions */
 int SECTION_HDR_SIZE ; 
 int /*<<< orphan*/  __verify_patch_section (int const*,size_t,size_t*,int) ; 
 unsigned int __verify_patch_size (int,size_t,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
verify_patch(u8 family, const u8 *buf, size_t buf_size, u32 *patch_size, bool early)
{
	struct microcode_header_amd *mc_hdr;
	unsigned int ret;
	u32 sh_psize;
	u16 proc_id;
	u8 patch_fam;

	if (!__verify_patch_section(buf, buf_size, &sh_psize, early))
		return -1;

	/*
	 * The section header length is not included in this indicated size
	 * but is present in the leftover file length so we need to subtract
	 * it before passing this value to the function below.
	 */
	buf_size -= SECTION_HDR_SIZE;

	/*
	 * Check if the remaining buffer is big enough to contain a patch of
	 * size sh_psize, as the section claims.
	 */
	if (buf_size < sh_psize) {
		if (!early)
			pr_debug("Patch of size %u truncated.\n", sh_psize);

		return -1;
	}

	ret = __verify_patch_size(family, sh_psize, buf_size);
	if (!ret) {
		if (!early)
			pr_debug("Per-family patch size mismatch.\n");
		return -1;
	}

	*patch_size = sh_psize;

	mc_hdr	= (struct microcode_header_amd *)(buf + SECTION_HDR_SIZE);
	if (mc_hdr->nb_dev_id || mc_hdr->sb_dev_id) {
		if (!early)
			pr_err("Patch-ID 0x%08x: chipset-specific code unsupported.\n", mc_hdr->patch_id);
		return -1;
	}

	proc_id	= mc_hdr->processor_rev_id;
	patch_fam = 0xf + (proc_id >> 12);
	if (patch_fam != family)
		return 1;

	return 0;
}