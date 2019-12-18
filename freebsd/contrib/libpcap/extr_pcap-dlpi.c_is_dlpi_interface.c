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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int /*<<< orphan*/  close (int) ; 
 int open_dlpi_device (char const*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
is_dlpi_interface(const char *name)
{
	int fd;
	u_int ppa;
	char errbuf[PCAP_ERRBUF_SIZE];

	fd = open_dlpi_device(name, &ppa, errbuf);
	if (fd < 0) {
		/*
		 * Error - was it PCAP_ERROR_NO_SUCH_DEVICE?
		 */
		if (fd == PCAP_ERROR_NO_SUCH_DEVICE) {
			/*
			 * Yes, so we can't open this because it's
			 * not a DLPI interface.
			 */
			return (0);
		}
		/*
		 * No, so, in the case where there's a single DLPI
		 * device for all interfaces of this type ("style
		 * 2" providers?), we don't know whether it's a DLPI
		 * interface or not, as we didn't try an attach.
		 * Say it is a DLPI device, so that the user can at
		 * least try to open it and report the error (which
		 * is probably "you don't have permission to open that
		 * DLPI device"; reporting those interfaces means
		 * users will ask "why am I getting a permissions error
		 * when I try to capture" rather than "why am I not
		 * seeing any interfaces", making the underlying problem
		 * clearer).
		 */
		return (1);
	}

	/*
	 * Success.
	 */
	close(fd);
	return (1);
}