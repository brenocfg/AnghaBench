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

/* Variables and functions */
 int /*<<< orphan*/  MODE_APPEND ; 
 scalar_t__ MODE_DEFAULT ; 
 int /*<<< orphan*/  MODE_EXTRACT ; 
 int add_data (char*) ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  crc32_filltable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_table ; 
 int extract_data (char*) ; 
 scalar_t__ file_mode ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ metadata_file ; 
 int /*<<< orphan*/  msg (char*) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int quiet ; 
 int set_file (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signature_file ; 
 int truncate_file ; 
 int usage (char const*) ; 

int main(int argc, char **argv)
{
	const char *progname = argv[0];
	int ret, ch;

	crc32_filltable(crc_table);

	while ((ch = getopt(argc, argv, "i:I:qs:S:t")) != -1) {
		ret = 0;
		switch(ch) {
		case 'S':
			ret = set_file(&signature_file, optarg, MODE_APPEND);
			break;
		case 'I':
			ret = set_file(&metadata_file, optarg, MODE_APPEND);
			break;
		case 's':
			ret = set_file(&signature_file, optarg, MODE_EXTRACT);
			break;
		case 'i':
			ret = set_file(&metadata_file, optarg, MODE_EXTRACT);
			break;
		case 't':
			truncate_file = true;
			break;
		case 'q':
			quiet = true;
			break;
		}

		if (ret)
			goto out;
	}

	if (optind >= argc) {
		ret = usage(progname);
		goto out;
	}

	if (file_mode == MODE_DEFAULT) {
		ret = usage(progname);
		goto out;
	}

	if (signature_file && metadata_file) {
		msg("Cannot append/extract metadata and signature in one run\n");
		return 1;
	}

	if (file_mode)
		ret = add_data(argv[optind]);
	else
		ret = extract_data(argv[optind]);

out:
	cleanup();
	return ret;
}