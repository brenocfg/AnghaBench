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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ V_VERBOSE ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 scalar_t__ mytime_get_elapsed () ; 
 int progress_active ; 
 scalar_t__ progress_automatic ; 
 char* progress_percentage (scalar_t__) ; 
 int /*<<< orphan*/  progress_pos (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 char* progress_remaining (scalar_t__,scalar_t__ const) ; 
 char* progress_sizes (scalar_t__,scalar_t__,int) ; 
 char* progress_speed (scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  progress_started ; 
 char* progress_time (scalar_t__ const) ; 
 int /*<<< orphan*/  signals_block () ; 
 int /*<<< orphan*/  signals_unblock () ; 
 int /*<<< orphan*/  stderr ; 
 char* tuklib_mbstr_fw (char const*,int) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void
progress_flush(bool finished)
{
	if (!progress_started || verbosity < V_VERBOSE)
		return;

	uint64_t in_pos;
	uint64_t compressed_pos;
	uint64_t uncompressed_pos;
	progress_pos(&in_pos, &compressed_pos, &uncompressed_pos);

	// Avoid printing intermediate progress info if some error occurs
	// in the beginning of the stream. (If something goes wrong later in
	// the stream, it is sometimes useful to tell the user where the
	// error approximately occurred, especially if the error occurs
	// after a time-consuming operation.)
	if (!finished && !progress_active
			&& (compressed_pos == 0 || uncompressed_pos == 0))
		return;

	progress_active = false;

	const uint64_t elapsed = mytime_get_elapsed();

	signals_block();

	// When using the auto-updating progress indicator, the final
	// statistics are printed in the same format as the progress
	// indicator itself.
	if (progress_automatic) {
		const char *cols[5] = {
			finished ? "100 %" : progress_percentage(in_pos),
			progress_sizes(compressed_pos, uncompressed_pos, true),
			progress_speed(uncompressed_pos, elapsed),
			progress_time(elapsed),
			finished ? "" : progress_remaining(in_pos, elapsed),
		};
		fprintf(stderr, "\r %*s %*s   %*s %10s   %10s\n",
				tuklib_mbstr_fw(cols[0], 6), cols[0],
				tuklib_mbstr_fw(cols[1], 35), cols[1],
				tuklib_mbstr_fw(cols[2], 9), cols[2],
				cols[3],
				cols[4]);
	} else {
		// The filename is always printed.
		fprintf(stderr, "%s: ", filename);

		// Percentage is printed only if we didn't finish yet.
		if (!finished) {
			// Don't print the percentage when it isn't known
			// (starts with a dash).
			const char *percentage = progress_percentage(in_pos);
			if (percentage[0] != '-')
				fprintf(stderr, "%s, ", percentage);
		}

		// Size information is always printed.
		fprintf(stderr, "%s", progress_sizes(
				compressed_pos, uncompressed_pos, true));

		// The speed and elapsed time aren't always shown.
		const char *speed = progress_speed(uncompressed_pos, elapsed);
		if (speed[0] != '\0')
			fprintf(stderr, ", %s", speed);

		const char *elapsed_str = progress_time(elapsed);
		if (elapsed_str[0] != '\0')
			fprintf(stderr, ", %s", elapsed_str);

		fputc('\n', stderr);
	}

	signals_unblock();

	return;
}