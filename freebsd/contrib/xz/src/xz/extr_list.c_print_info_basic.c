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
struct TYPE_5__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_1__ xz_file_info ;
struct TYPE_6__ {char* src_name; } ;
typedef  TYPE_2__ file_pair ;

/* Variables and functions */
 int CHECKS_STR_SIZE ; 
 int /*<<< orphan*/  NICESTR_B ; 
 int /*<<< orphan*/  NICESTR_TIB ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_check_names (char*,int /*<<< orphan*/ ,int) ; 
 char* get_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_block_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_checks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_file_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_stream_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_uncompressed_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 char* tuklib_mbstr_fw (char const*,int) ; 
 char* uint64_to_nicestr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 char* uint64_to_str (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
print_info_basic(const xz_file_info *xfi, file_pair *pair)
{
	static bool headings_displayed = false;
	if (!headings_displayed) {
		headings_displayed = true;
		// TRANSLATORS: These are column headings. From Strms (Streams)
		// to Ratio, the columns are right aligned. Check and Filename
		// are left aligned. If you need longer words, it's OK to
		// use two lines here. Test with "xz -l foo.xz".
		puts(_("Strms  Blocks   Compressed Uncompressed  Ratio  "
				"Check   Filename"));
	}

	char checks[CHECKS_STR_SIZE];
	get_check_names(checks, lzma_index_checks(xfi->idx), false);

	const char *cols[7] = {
		uint64_to_str(lzma_index_stream_count(xfi->idx), 0),
		uint64_to_str(lzma_index_block_count(xfi->idx), 1),
		uint64_to_nicestr(lzma_index_file_size(xfi->idx),
			NICESTR_B, NICESTR_TIB, false, 2),
		uint64_to_nicestr(lzma_index_uncompressed_size(xfi->idx),
			NICESTR_B, NICESTR_TIB, false, 3),
		get_ratio(lzma_index_file_size(xfi->idx),
			lzma_index_uncompressed_size(xfi->idx)),
		checks,
		pair->src_name,
	};
	printf("%*s %*s  %*s  %*s  %*s  %-*s %s\n",
			tuklib_mbstr_fw(cols[0], 5), cols[0],
			tuklib_mbstr_fw(cols[1], 7), cols[1],
			tuklib_mbstr_fw(cols[2], 11), cols[2],
			tuklib_mbstr_fw(cols[3], 11), cols[3],
			tuklib_mbstr_fw(cols[4], 5), cols[4],
			tuklib_mbstr_fw(cols[5], 7), cols[5],
			cols[6]);

	return false;
}