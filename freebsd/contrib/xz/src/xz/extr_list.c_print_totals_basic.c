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
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {int streams; int blocks; int files; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  compressed_size; int /*<<< orphan*/  checks; } ;

/* Variables and functions */
 int CHECKS_STR_SIZE ; 
 int /*<<< orphan*/  NICESTR_B ; 
 int /*<<< orphan*/  NICESTR_TIB ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  get_check_names (char*,int /*<<< orphan*/ ,int) ; 
 char* get_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 char* ngettext (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 TYPE_1__ totals ; 
 char* uint64_to_nicestr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 char* uint64_to_str (int,int) ; 

__attribute__((used)) static void
print_totals_basic(void)
{
	// Print a separator line.
	char line[80];
	memset(line, '-', sizeof(line));
	line[sizeof(line) - 1] = '\0';
	puts(line);

	// Get the check names.
	char checks[CHECKS_STR_SIZE];
	get_check_names(checks, totals.checks, false);

	// Print the totals except the file count, which needs
	// special handling.
	printf("%5s %7s  %11s  %11s  %5s  %-7s ",
			uint64_to_str(totals.streams, 0),
			uint64_to_str(totals.blocks, 1),
			uint64_to_nicestr(totals.compressed_size,
				NICESTR_B, NICESTR_TIB, false, 2),
			uint64_to_nicestr(totals.uncompressed_size,
				NICESTR_B, NICESTR_TIB, false, 3),
			get_ratio(totals.compressed_size,
				totals.uncompressed_size),
			checks);

	// Since we print totals only when there are at least two files,
	// the English message will always use "%s files". But some other
	// languages need different forms for different plurals so we
	// have to translate this with ngettext().
	//
	// TRANSLATORS: %s is an integer. Only the plural form of this
	// message is used (e.g. "2 files"). Test with "xz -l foo.xz bar.xz".
	printf(ngettext("%s file\n", "%s files\n",
			totals.files <= ULONG_MAX ? totals.files
				: (totals.files % 1000000) + 1000000),
			uint64_to_str(totals.files, 0));

	return;
}