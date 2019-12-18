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
typedef  int /*<<< orphan*/  uint8 ;
struct pcap_rmtauth {int dummy; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  RPCAP_MAX_VERSION ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int rpcap_sendauth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pcap_rmtauth*,char*) ; 

__attribute__((used)) static int rpcap_doauth(SOCKET sockctrl, uint8 *ver, struct pcap_rmtauth *auth, char *errbuf)
{
	int status;

	/*
	 * Send authentication to the remote machine.
	 *
	 * First try with the maximum version number we support.
	 */
	*ver = RPCAP_MAX_VERSION;
	status = rpcap_sendauth(sockctrl, ver, auth, errbuf);
	if (status == 0)
	{
		//
		// Success.
		//
		return 0;
	}
	if (status == -1)
	{
		/* Unrecoverable error. */
		return -1;
	}

	/*
	 * The server doesn't support the version we used in the initial
	 * message, and it sent us back a reply either with the maximum
	 * version they do support, or with the version we sent, and we
	 * support that version.  *ver has been set to that version; try
	 * authenticating again with that version.
	 */
	status = rpcap_sendauth(sockctrl, ver, auth, errbuf);
	if (status == 0)
	{
		//
		// Success.
		//
		return 0;
	}
	if (status == -1)
	{
		/* Unrecoverable error. */
		return -1;
	}
	if (status == -2)
	{
		/*
		 * The server doesn't support that version, which
		 * means there is no version we both support, so
		 * this is a fatal error.
		 */
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "The server doesn't support any protocol version that we support");
		return -1;
	}
	pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "rpcap_sendauth() returned %d", status);
	return -1;
}