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
struct TYPE_2__ {int /*<<< orphan*/  min_version; scalar_t__ all_have_sizes; int /*<<< orphan*/  memusage_max; int /*<<< orphan*/  stream_padding; int /*<<< orphan*/  checks; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  compressed_size; int /*<<< orphan*/  blocks; int /*<<< orphan*/  streams; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 scalar_t__ V_DEBUG ; 
 char* _ (char*) ; 
 scalar_t__ message_verbosity_get () ; 
 int /*<<< orphan*/  print_adv_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  round_up_to_mib (int /*<<< orphan*/ ) ; 
 TYPE_1__ totals ; 
 char* uint64_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xz_ver_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_totals_adv(void)
{
	putchar('\n');
	puts(_("Totals:"));
	printf(_("  Number of files:    %s\n"),
			uint64_to_str(totals.files, 0));
	print_adv_helper(totals.streams, totals.blocks,
			totals.compressed_size, totals.uncompressed_size,
			totals.checks, totals.stream_padding);

	if (message_verbosity_get() >= V_DEBUG) {
		printf(_("  Memory needed:      %s MiB\n"), uint64_to_str(
				round_up_to_mib(totals.memusage_max), 0));
		printf(_("  Sizes in headers:   %s\n"),
				totals.all_have_sizes ? _("Yes") : _("No"));
		printf(_("  Minimum XZ Utils version: %s\n"),
				xz_ver_to_str(totals.min_version));
	}

	return;
}