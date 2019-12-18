#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int debug_level; TYPE_1__* logconfig; } ;
typedef  TYPE_2__ isc_log_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_4__ {int highest_level; scalar_t__ dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TF (int) ; 

isc_boolean_t
isc_log_wouldlog(isc_log_t *lctx, int level) {
	/*
	 * Try to avoid locking the mutex for messages which can't
	 * possibly be logged to any channels -- primarily debugging
	 * messages that the debug level is not high enough to print.
	 *
	 * If the level is (mathematically) less than or equal to the
	 * highest_level, or if there is a dynamic channel and the level is
	 * less than or equal to the debug level, the main loop must be
	 * entered to see if the message should really be output.
	 *
	 * NOTE: this is UNLOCKED access to the logconfig.  However,
	 * the worst thing that can happen is that a bad decision is made
	 * about returning without logging, and that's not a big concern,
	 * because that's a risk anyway if the logconfig is being
	 * dynamically changed.
	 */

	if (lctx == NULL || lctx->logconfig == NULL)
		return (ISC_FALSE);

	return (ISC_TF(level <= lctx->logconfig->highest_level ||
		       (lctx->logconfig->dynamic &&
			level <= lctx->debug_level)));
}