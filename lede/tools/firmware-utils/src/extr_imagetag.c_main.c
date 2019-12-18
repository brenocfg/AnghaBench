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
typedef  scalar_t__ uint32_t ;
struct gengetopt_args_info {char* kernel_arg; char* rootfs_arg; char* output_arg; scalar_t__ pad_arg; int /*<<< orphan*/  entry_arg; int /*<<< orphan*/  load_addr_arg; int /*<<< orphan*/  kernel_file_has_header_flag; int /*<<< orphan*/  block_size_arg; int /*<<< orphan*/  image_offset_arg; int /*<<< orphan*/  flash_start_arg; scalar_t__ pad_given; int /*<<< orphan*/  altinfo_arg; scalar_t__ altinfo_given; int /*<<< orphan*/  info2_arg; scalar_t__ info2_given; int /*<<< orphan*/  info1_arg; scalar_t__ info1_given; int /*<<< orphan*/  rsa_signature_arg; scalar_t__ rsa_signature_given; int /*<<< orphan*/  layoutver_arg; scalar_t__ layoutver_given; int /*<<< orphan*/  signature2_arg; int /*<<< orphan*/  signature_arg; int /*<<< orphan*/  chipid_arg; int /*<<< orphan*/  boardid_arg; int /*<<< orphan*/  tag_version_arg; } ;

/* Variables and functions */
 scalar_t__ ALTTAGINFO_LEN ; 
 scalar_t__ BOARDID_LEN ; 
 scalar_t__ CHIPID_LEN ; 
 scalar_t__ FLASHLAYOUTVER_LEN ; 
 scalar_t__ RSASIG_LEN ; 
 scalar_t__ SIG1_LEN ; 
 scalar_t__ SIG2_LEN ; 
 scalar_t__ TAGINFO1_LEN ; 
 scalar_t__ TAGINFO2_LEN ; 
 scalar_t__ TAGVER_LEN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ imagetag_cmdline (int,char**,struct gengetopt_args_info*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int tagfile (char*,char*,char*,struct gengetopt_args_info*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int main(int argc, char **argv)
{
    int c, i;
	char *kernel, *rootfs, *bin;
	uint32_t flash_start, image_offset, block_size, load_address, entry;
	flash_start = image_offset = block_size = load_address = entry = 0;
	struct gengetopt_args_info parsed_args;

	kernel = rootfs = bin = NULL;

	if (imagetag_cmdline(argc, argv, &parsed_args)) {
	  exit(1);
	}

	printf("Broadcom 63xx image tagger - v2.0.0\n");
	printf("Copyright (C) 2008 Axel Gembe\n");
	printf("Copyright (C) 2009-2010 Daniel Dickinson\n");
	printf("Licensed under the terms of the Gnu General Public License\n");

	kernel = parsed_args.kernel_arg;
	rootfs = parsed_args.rootfs_arg;
	bin = parsed_args.output_arg;
	if (strlen(parsed_args.tag_version_arg) >= TAGVER_LEN) {
	  fprintf(stderr, "Error: Tag Version (tag_version,v) too long.\n");
	  exit(1);
	}
	if (strlen(parsed_args.boardid_arg) >= BOARDID_LEN) {
	  fprintf(stderr, "Error: Board ID (boardid,b) too long.\n");
	  exit(1);
	}
	if (strlen(parsed_args.chipid_arg) >= CHIPID_LEN) {
	  fprintf(stderr, "Error: Chip ID (chipid,c) too long.\n");
	  exit(1);
	}
	if (strlen(parsed_args.signature_arg) >= SIG1_LEN) {
	  fprintf(stderr, "Error: Magic string (signature,a) too long.\n");
	  exit(1);
	}
	if (strlen(parsed_args.signature2_arg) >= SIG2_LEN) {
	  fprintf(stderr, "Error: Second magic string (signature2,m) too long.\n");
	  exit(1);
	}
	if (parsed_args.layoutver_given) {
	  if (strlen(parsed_args.layoutver_arg) > FLASHLAYOUTVER_LEN) {
		fprintf(stderr, "Error: Flash layout version (layoutver,y) too long.\n");
		exit(1);
	  }
	}
	if (parsed_args.rsa_signature_given) {
	  if (strlen(parsed_args.rsa_signature_arg) > RSASIG_LEN) {
		fprintf(stderr, "Error: RSA Signature (rsa_signature,r) too long.\n");
		exit(1);
	  }
	}

	if (parsed_args.info1_given) {
	  if (strlen(parsed_args.info1_arg) >= TAGINFO1_LEN) {
		fprintf(stderr, "Error: Vendor Information 1 (info1) too long.\n");
		exit(1);
	  }
	}

	if (parsed_args.info2_given) {
	  if (strlen(parsed_args.info2_arg) >= TAGINFO2_LEN) {
		fprintf(stderr, "Error: Vendor Information 2 (info2) too long.\n");
		exit(1);
	  }
	}

	if (parsed_args.altinfo_given) {
	  if (strlen(parsed_args.altinfo_arg) >= ALTTAGINFO_LEN) {
		fprintf(stderr, "Error: Vendor Information 1 (info1) too long.\n");
		exit(1);
	  }
	}

	if (parsed_args.pad_given) {
	  if (parsed_args.pad_arg < 0) {
		fprintf(stderr, "Error: pad size must be positive.\r");
		exit(1);
	  }
	}

	flash_start = strtoul(parsed_args.flash_start_arg, NULL, 16);
	image_offset = strtoul(parsed_args.image_offset_arg, NULL, 16);
	block_size = strtoul(parsed_args.block_size_arg, NULL, 16);

	if (!parsed_args.kernel_file_has_header_flag) {
	  load_address = strtoul(parsed_args.load_addr_arg, NULL, 16);
	  entry = strtoul(parsed_args.entry_arg, NULL, 16);
	  if (load_address == 0) {
		fprintf(stderr, "Error: Invalid value for load address\n");
	  }
	  if (entry == 0) {
		fprintf(stderr, "Error: Invalid value for entry\n");
	  }
	}
	
	return tagfile(kernel, rootfs, bin, &parsed_args, flash_start, image_offset, block_size, load_address, entry);
}