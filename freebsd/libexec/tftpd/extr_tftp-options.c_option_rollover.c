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
struct TYPE_2__ {int /*<<< orphan*/ * o_reply; int /*<<< orphan*/ * o_request; } ;

/* Variables and functions */
 int DEBUG_OPTIONS ; 
 int /*<<< orphan*/  EBADOP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 size_t OPT_ROLLOVER ; 
 scalar_t__ acting_as_client ; 
 int debug ; 
 TYPE_1__* options ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int
option_rollover(int peer)
{

	if (options[OPT_ROLLOVER].o_request == NULL)
		return (0);

	if (strcmp(options[OPT_ROLLOVER].o_request, "0") != 0
	 && strcmp(options[OPT_ROLLOVER].o_request, "1") != 0) {
		tftp_log(acting_as_client ? LOG_ERR : LOG_WARNING,
		    "Bad value for rollover, "
		    "should be either 0 or 1, received '%s', "
		    "ignoring request",
		    options[OPT_ROLLOVER].o_request);
		if (acting_as_client) {
			send_error(peer, EBADOP);
			return (1);
		}
		return (0);
	}
	options[OPT_ROLLOVER].o_reply =
		strdup(options[OPT_ROLLOVER].o_request);

	if (debug&DEBUG_OPTIONS)
		tftp_log(LOG_DEBUG, "Setting rollover to '%s'",
			options[OPT_ROLLOVER].o_reply);

	return (0);
}