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
typedef  int /*<<< orphan*/  lzma_stream ;

/* Variables and functions */
 scalar_t__ V_VERBOSE ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  expected_in_size ; 
 scalar_t__ progress_automatic ; 
 int progress_needs_updating ; 
 int progress_next_update ; 
 int progress_started ; 
 int /*<<< orphan*/ * progress_strm ; 
 scalar_t__ verbosity ; 

extern void
message_progress_start(lzma_stream *strm, uint64_t in_size)
{
	// Store the pointer to the lzma_stream used to do the coding.
	// It is needed to find out the position in the stream.
	progress_strm = strm;

	// Store the expected size of the file. If we aren't printing any
	// statistics, then is will be unused. But since it is possible
	// that the user sends us a signal to show statistics, we need
	// to have it available anyway.
	expected_in_size = in_size;

	// Indicate that progress info may need to be printed before
	// printing error messages.
	progress_started = true;

	// If progress indicator is wanted, print the filename and possibly
	// the file count now.
	if (verbosity >= V_VERBOSE && progress_automatic) {
		// Start the timer to display the first progress message
		// after one second. An alternative would be to show the
		// first message almost immediately, but delaying by one
		// second looks better to me, since extremely early
		// progress info is pretty much useless.
#ifdef SIGALRM
		// First disable a possibly existing alarm.
		alarm(0);
		progress_needs_updating = false;
		alarm(1);
#else
		progress_needs_updating = true;
		progress_next_update = 1000;
#endif
	}

	return;
}