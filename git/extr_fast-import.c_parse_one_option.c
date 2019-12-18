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
 unsigned long big_file_threshold ; 
 int /*<<< orphan*/  git_parse_ulong (char const*,unsigned long*) ; 
 unsigned long max_packsize ; 
 int /*<<< orphan*/  option_active_branches (char const*) ; 
 int /*<<< orphan*/  option_depth (char const*) ; 
 int /*<<< orphan*/  option_export_pack_edges (char const*) ; 
 int show_stats ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static int parse_one_option(const char *option)
{
	if (skip_prefix(option, "max-pack-size=", &option)) {
		unsigned long v;
		if (!git_parse_ulong(option, &v))
			return 0;
		if (v < 8192) {
			warning("max-pack-size is now in bytes, assuming --max-pack-size=%lum", v);
			v *= 1024 * 1024;
		} else if (v < 1024 * 1024) {
			warning("minimum max-pack-size is 1 MiB");
			v = 1024 * 1024;
		}
		max_packsize = v;
	} else if (skip_prefix(option, "big-file-threshold=", &option)) {
		unsigned long v;
		if (!git_parse_ulong(option, &v))
			return 0;
		big_file_threshold = v;
	} else if (skip_prefix(option, "depth=", &option)) {
		option_depth(option);
	} else if (skip_prefix(option, "active-branches=", &option)) {
		option_active_branches(option);
	} else if (skip_prefix(option, "export-pack-edges=", &option)) {
		option_export_pack_edges(option);
	} else if (starts_with(option, "quiet")) {
		show_stats = 0;
	} else if (starts_with(option, "stats")) {
		show_stats = 1;
	} else {
		return 0;
	}

	return 1;
}