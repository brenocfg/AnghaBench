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
typedef  int uint64_t ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct progress {int dummy; } ;
struct option {int dummy; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct option OPT_END () ; 
 struct option OPT_INTEGER (int /*<<< orphan*/ ,char*,int*,char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  display_progress (struct progress*,int) ; 
 int /*<<< orphan*/  display_throughput (struct progress*,int) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progress_test_force_update () ; 
 int progress_test_ns ; 
 int progress_testing ; 
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 struct progress* start_progress (char const*,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strtoull (char*,char**,int) ; 

int cmd__progress(int argc, const char **argv)
{
	int total = 0;
	const char *title;
	struct strbuf line = STRBUF_INIT;
	struct progress *progress;

	const char *usage[] = {
		"test-tool progress [--total=<n>] <progress-title>",
		NULL
	};
	struct option options[] = {
		OPT_INTEGER(0, "total", &total, "total number of items"),
		OPT_END(),
	};

	argc = parse_options(argc, argv, NULL, options, usage, 0);
	if (argc != 1)
		die("need a title for the progress output");
	title = argv[0];

	progress_testing = 1;
	progress = start_progress(title, total);
	while (strbuf_getline(&line, stdin) != EOF) {
		char *end;

		if (skip_prefix(line.buf, "progress ", (const char **) &end)) {
			uint64_t item_count = strtoull(end, &end, 10);
			if (*end != '\0')
				die("invalid input: '%s'\n", line.buf);
			display_progress(progress, item_count);
		} else if (skip_prefix(line.buf, "throughput ",
				       (const char **) &end)) {
			uint64_t byte_count, test_ms;

			byte_count = strtoull(end, &end, 10);
			if (*end != ' ')
				die("invalid input: '%s'\n", line.buf);
			test_ms = strtoull(end + 1, &end, 10);
			if (*end != '\0')
				die("invalid input: '%s'\n", line.buf);
			progress_test_ns = test_ms * 1000 * 1000;
			display_throughput(progress, byte_count);
		} else if (!strcmp(line.buf, "update"))
			progress_test_force_update();
		else
			die("invalid input: '%s'\n", line.buf);
	}
	stop_progress(&progress);

	return 0;
}