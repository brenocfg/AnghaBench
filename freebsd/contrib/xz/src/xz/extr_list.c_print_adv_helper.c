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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int CHECKS_STR_SIZE ; 
 int /*<<< orphan*/  NICESTR_B ; 
 int /*<<< orphan*/  NICESTR_TIB ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  get_check_names (char*,int /*<<< orphan*/ ,int) ; 
 char* get_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* uint64_to_nicestr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* uint64_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_adv_helper(uint64_t stream_count, uint64_t block_count,
		uint64_t compressed_size, uint64_t uncompressed_size,
		uint32_t checks, uint64_t stream_padding)
{
	char checks_str[CHECKS_STR_SIZE];
	get_check_names(checks_str, checks, true);

	printf(_("  Streams:            %s\n"),
			uint64_to_str(stream_count, 0));
	printf(_("  Blocks:             %s\n"),
			uint64_to_str(block_count, 0));
	printf(_("  Compressed size:    %s\n"),
			uint64_to_nicestr(compressed_size,
				NICESTR_B, NICESTR_TIB, true, 0));
	printf(_("  Uncompressed size:  %s\n"),
			uint64_to_nicestr(uncompressed_size,
				NICESTR_B, NICESTR_TIB, true, 0));
	printf(_("  Ratio:              %s\n"),
			get_ratio(compressed_size, uncompressed_size));
	printf(_("  Check:              %s\n"), checks_str);
	printf(_("  Stream padding:     %s\n"),
			uint64_to_nicestr(stream_padding,
				NICESTR_B, NICESTR_TIB, true, 0));
	return;
}