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
typedef  int /*<<< orphan*/  memlimitstr ;
typedef  enum message_verbosity { ____Placeholder_message_verbosity } message_verbosity ;

/* Variables and functions */
 int UINT32_C (int) ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int hardware_memlimit_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  opt_mode ; 
 int round_up_to_mib (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* uint64_to_str (int,int) ; 
 int verbosity ; 

extern void
message_mem_needed(enum message_verbosity v, uint64_t memusage)
{
	if (v > verbosity)
		return;

	// Convert memusage to MiB, rounding up to the next full MiB.
	// This way the user can always use the displayed usage as
	// the new memory usage limit. (If we rounded to the nearest,
	// the user might need to +1 MiB to get high enough limit.)
	memusage = round_up_to_mib(memusage);

	uint64_t memlimit = hardware_memlimit_get(opt_mode);

	// Handle the case when there is no memory usage limit.
	// This way we don't print a weird message with a huge number.
	if (memlimit == UINT64_MAX) {
		message(v, _("%s MiB of memory is required. "
				"The limiter is disabled."),
				uint64_to_str(memusage, 0));
		return;
	}

	// With US-ASCII:
	// 2^64 with thousand separators + " MiB" suffix + '\0' = 26 + 4 + 1
	// But there may be multibyte chars so reserve enough space.
	char memlimitstr[128];

	// Show the memory usage limit as MiB unless it is less than 1 MiB.
	// This way it's easy to notice errors where one has typed
	// --memory=123 instead of --memory=123MiB.
	if (memlimit < (UINT32_C(1) << 20)) {
		snprintf(memlimitstr, sizeof(memlimitstr), "%s B",
				uint64_to_str(memlimit, 1));
	} else {
		// Round up just like with memusage. If this function is
		// called for informational purposes (to just show the
		// current usage and limit), we should never show that
		// the usage is higher than the limit, which would give
		// a false impression that the memory usage limit isn't
		// properly enforced.
		snprintf(memlimitstr, sizeof(memlimitstr), "%s MiB",
				uint64_to_str(round_up_to_mib(memlimit), 1));
	}

	message(v, _("%s MiB of memory is required. The limit is %s."),
			uint64_to_str(memusage, 0), memlimitstr);

	return;
}