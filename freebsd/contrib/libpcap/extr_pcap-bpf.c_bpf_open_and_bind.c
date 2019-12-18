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
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOCSETIF ; 
#define  ENETDOWN 129 
#define  ENXIO 128 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_IFACE_NOT_UP ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int bpf_open (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
bpf_open_and_bind(const char *name, char *errbuf)
{
	int fd;
	struct ifreq ifr;

	/*
	 * First, open a BPF device.
	 */
	fd = bpf_open(errbuf);
	if (fd < 0)
		return (fd);	/* fd is the appropriate error code */

	/*
	 * Now bind to the device.
	 */
	(void)strncpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	if (ioctl(fd, BIOCSETIF, (caddr_t)&ifr) < 0) {
		switch (errno) {

		case ENXIO:
			/*
			 * There's no such device.
			 */
			close(fd);
			return (PCAP_ERROR_NO_SUCH_DEVICE);

		case ENETDOWN:
			/*
			 * Return a "network down" indication, so that
			 * the application can report that rather than
			 * saying we had a mysterious failure and
			 * suggest that they report a problem to the
			 * libpcap developers.
			 */
			close(fd);
			return (PCAP_ERROR_IFACE_NOT_UP);

		default:
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "BIOCSETIF: %s", name);
			close(fd);
			return (PCAP_ERROR);
		}
	}

	/*
	 * Success.
	 */
	return (fd);
}