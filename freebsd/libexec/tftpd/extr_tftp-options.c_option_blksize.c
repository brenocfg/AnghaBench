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
typedef  int u_long ;
typedef  int /*<<< orphan*/  maxdgram ;
struct TYPE_2__ {int o_reply; int /*<<< orphan*/ * o_request; } ;

/* Variables and functions */
 int BLKSIZE_MAX ; 
 int BLKSIZE_MIN ; 
 int DEBUG_OPTIONS ; 
 int /*<<< orphan*/  EBADOP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 size_t OPT_BLKSIZE ; 
 scalar_t__ acting_as_client ; 
 int /*<<< orphan*/  asprintf (int*,char*,int) ; 
 int atoi (int /*<<< orphan*/ *) ; 
 int debug ; 
 TYPE_1__* options ; 
 int pktsize ; 
 int segsize ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,...) ; 

int
option_blksize(int peer)
{
	u_long maxdgram;
	size_t len;

	if (options[OPT_BLKSIZE].o_request == NULL)
		return (0);

	/* maximum size of an UDP packet according to the system */
	len = sizeof(maxdgram);
	if (sysctlbyname("net.inet.udp.maxdgram",
	    &maxdgram, &len, NULL, 0) < 0) {
		tftp_log(LOG_ERR, "sysctl: net.inet.udp.maxdgram");
		return (acting_as_client ? 1 : 0);
	}

	int size = atoi(options[OPT_BLKSIZE].o_request);
	if (size < BLKSIZE_MIN || size > BLKSIZE_MAX) {
		if (acting_as_client) {
			tftp_log(LOG_ERR,
			    "Invalid blocksize (%d bytes), aborting",
			    size);
			send_error(peer, EBADOP);
			return (1);
		} else {
			tftp_log(LOG_WARNING,
			    "Invalid blocksize (%d bytes), ignoring request",
			    size);
			return (0);
		}
	}

	if (size > (int)maxdgram) {
		if (acting_as_client) {
			tftp_log(LOG_ERR,
			    "Invalid blocksize (%d bytes), "
			    "net.inet.udp.maxdgram sysctl limits it to "
			    "%ld bytes.\n", size, maxdgram);
			send_error(peer, EBADOP);
			return (1);
		} else {
			tftp_log(LOG_WARNING,
			    "Invalid blocksize (%d bytes), "
			    "net.inet.udp.maxdgram sysctl limits it to "
			    "%ld bytes.\n", size, maxdgram);
			size = maxdgram;
			/* No reason to return */
		}
	}

	asprintf(&options[OPT_BLKSIZE].o_reply, "%d", size);
	segsize = size;
	pktsize = size + 4;
	if (debug&DEBUG_OPTIONS)
		tftp_log(LOG_DEBUG, "Setting blksize to '%s'",
		    options[OPT_BLKSIZE].o_reply);

	return (0);
}