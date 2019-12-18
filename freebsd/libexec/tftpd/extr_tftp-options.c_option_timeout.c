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
struct TYPE_2__ {int /*<<< orphan*/  o_reply; int /*<<< orphan*/ * o_request; } ;

/* Variables and functions */
 int DEBUG_OPTIONS ; 
 int /*<<< orphan*/  EBADOP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 size_t OPT_TIMEOUT ; 
 int TIMEOUT_MAX ; 
 int TIMEOUT_MIN ; 
 scalar_t__ acting_as_client ; 
 int atoi (int /*<<< orphan*/ *) ; 
 int debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  maxtimeouts ; 
 TYPE_1__* options ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settimeouts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  timeoutnetwork ; 
 int timeoutpacket ; 

int
option_timeout(int peer)
{
	int to;

	if (options[OPT_TIMEOUT].o_request == NULL)
		return (0);

	to = atoi(options[OPT_TIMEOUT].o_request);
	if (to < TIMEOUT_MIN || to > TIMEOUT_MAX) {
		tftp_log(acting_as_client ? LOG_ERR : LOG_WARNING,
		    "Received bad value for timeout. "
		    "Should be between %d and %d, received %d",
		    TIMEOUT_MIN, TIMEOUT_MAX, to);
		send_error(peer, EBADOP);
		if (acting_as_client)
			return (1);
		exit(1);
	} else {
		timeoutpacket = to;
		options[OPT_TIMEOUT].o_reply =
			strdup(options[OPT_TIMEOUT].o_request);
	}
	settimeouts(timeoutpacket, timeoutnetwork, maxtimeouts);

	if (debug&DEBUG_OPTIONS)
		tftp_log(LOG_DEBUG, "Setting timeout to '%s'",
			options[OPT_TIMEOUT].o_reply);

	return (0);
}