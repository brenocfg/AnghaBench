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
struct gengetopt_args_info {scalar_t__ align_rootfs_flag; int /*<<< orphan*/ * pad_orig; scalar_t__ kernel_file_has_header_flag; int /*<<< orphan*/ * reserved2_orig; int /*<<< orphan*/ * reserved2_arg; int /*<<< orphan*/ * inactive_orig; void* inactive_arg; int /*<<< orphan*/ * second_image_flag_orig; void* second_image_flag_arg; int /*<<< orphan*/ * rsa_signature_orig; int /*<<< orphan*/ * rsa_signature_arg; scalar_t__ root_first_flag; int /*<<< orphan*/ * info2_orig; int /*<<< orphan*/ * info2_arg; int /*<<< orphan*/ * altinfo_orig; int /*<<< orphan*/ * altinfo_arg; int /*<<< orphan*/ * info1_orig; int /*<<< orphan*/ * info1_arg; int /*<<< orphan*/ * layoutver_orig; int /*<<< orphan*/ * layoutver_arg; int /*<<< orphan*/ * entry_orig; int /*<<< orphan*/ * entry_arg; int /*<<< orphan*/ * load_addr_orig; int /*<<< orphan*/ * load_addr_arg; int /*<<< orphan*/ * block_size_orig; void* block_size_arg; int /*<<< orphan*/ * signature2_orig; void* signature2_arg; int /*<<< orphan*/ * signature_orig; void* signature_arg; int /*<<< orphan*/ * tag_version_orig; void* tag_version_arg; int /*<<< orphan*/ * image_offset_orig; void* image_offset_arg; int /*<<< orphan*/ * flash_start_orig; void* flash_start_arg; int /*<<< orphan*/ * chipid_orig; int /*<<< orphan*/ * chipid_arg; int /*<<< orphan*/ * boardid_orig; int /*<<< orphan*/ * boardid_arg; int /*<<< orphan*/ * cfe_orig; int /*<<< orphan*/ * cfe_arg; int /*<<< orphan*/ * output_orig; int /*<<< orphan*/ * output_arg; int /*<<< orphan*/ * rootfs_orig; int /*<<< orphan*/ * rootfs_arg; int /*<<< orphan*/ * kernel_orig; int /*<<< orphan*/ * kernel_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_UNUSED (struct gengetopt_args_info*) ; 
 void* gengetopt_strdup (char*) ; 

__attribute__((used)) static
void clear_args (struct gengetopt_args_info *args_info)
{
  FIX_UNUSED (args_info);
  args_info->kernel_arg = NULL;
  args_info->kernel_orig = NULL;
  args_info->rootfs_arg = NULL;
  args_info->rootfs_orig = NULL;
  args_info->output_arg = NULL;
  args_info->output_orig = NULL;
  args_info->cfe_arg = NULL;
  args_info->cfe_orig = NULL;
  args_info->boardid_arg = NULL;
  args_info->boardid_orig = NULL;
  args_info->chipid_arg = NULL;
  args_info->chipid_orig = NULL;
  args_info->flash_start_arg = gengetopt_strdup ("0xBFC00000");
  args_info->flash_start_orig = NULL;
  args_info->image_offset_arg = gengetopt_strdup ("0x10000");
  args_info->image_offset_orig = NULL;
  args_info->tag_version_arg = gengetopt_strdup ("6");
  args_info->tag_version_orig = NULL;
  args_info->signature_arg = gengetopt_strdup ("Broadcom Corporatio");
  args_info->signature_orig = NULL;
  args_info->signature2_arg = gengetopt_strdup ("ver. 2.0");
  args_info->signature2_orig = NULL;
  args_info->block_size_arg = gengetopt_strdup ("0x10000");
  args_info->block_size_orig = NULL;
  args_info->load_addr_arg = NULL;
  args_info->load_addr_orig = NULL;
  args_info->entry_arg = NULL;
  args_info->entry_orig = NULL;
  args_info->layoutver_arg = NULL;
  args_info->layoutver_orig = NULL;
  args_info->info1_arg = NULL;
  args_info->info1_orig = NULL;
  args_info->altinfo_arg = NULL;
  args_info->altinfo_orig = NULL;
  args_info->info2_arg = NULL;
  args_info->info2_orig = NULL;
  args_info->root_first_flag = 0;
  args_info->rsa_signature_arg = NULL;
  args_info->rsa_signature_orig = NULL;
  args_info->second_image_flag_arg = gengetopt_strdup ("2");
  args_info->second_image_flag_orig = NULL;
  args_info->inactive_arg = gengetopt_strdup ("2");
  args_info->inactive_orig = NULL;
  args_info->reserved2_arg = NULL;
  args_info->reserved2_orig = NULL;
  args_info->kernel_file_has_header_flag = 0;
  args_info->pad_orig = NULL;
  args_info->align_rootfs_flag = 0;
  
}