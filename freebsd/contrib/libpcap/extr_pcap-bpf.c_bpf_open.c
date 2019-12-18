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
typedef  int /*<<< orphan*/  device ;

/* Variables and functions */
#define  EACCES 129 
 int EBUSY ; 
#define  ENOENT 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int bpf_load (char*) ; 
 int errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int
bpf_open(char *errbuf)
{
	int fd = -1;
	static const char cloning_device[] = "/dev/bpf";
	int n = 0;
	char device[sizeof "/dev/bpf0000000000"];
	static int no_cloning_bpf = 0;

#ifdef _AIX
	/*
	 * Load the bpf driver, if it isn't already loaded,
	 * and create the BPF device entries, if they don't
	 * already exist.
	 */
	if (bpf_load(errbuf) == PCAP_ERROR)
		return (PCAP_ERROR);
#endif

	/*
	 * First, unless we've already tried opening /dev/bpf and
	 * gotten ENOENT, try opening /dev/bpf.
	 * If it fails with ENOENT, remember that, so we don't try
	 * again, and try /dev/bpfN.
	 */
	if (!no_cloning_bpf &&
	    (fd = open(cloning_device, O_RDWR)) == -1 &&
	    ((errno != EACCES && errno != ENOENT) ||
	     (fd = open(cloning_device, O_RDONLY)) == -1)) {
		if (errno != ENOENT) {
			if (errno == EACCES)
				fd = PCAP_ERROR_PERM_DENIED;
			else
				fd = PCAP_ERROR;
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "(cannot open device) %s", cloning_device);
			return (fd);
		}
		no_cloning_bpf = 1;
	}

	if (no_cloning_bpf) {
		/*
		 * We don't have /dev/bpf.
		 * Go through all the /dev/bpfN minors and find one
		 * that isn't in use.
		 */
		do {
			(void)pcap_snprintf(device, sizeof(device), "/dev/bpf%d", n++);
			/*
			 * Initially try a read/write open (to allow the inject
			 * method to work).  If that fails due to permission
			 * issues, fall back to read-only.  This allows a
			 * non-root user to be granted specific access to pcap
			 * capabilities via file permissions.
			 *
			 * XXX - we should have an API that has a flag that
			 * controls whether to open read-only or read-write,
			 * so that denial of permission to send (or inability
			 * to send, if sending packets isn't supported on
			 * the device in question) can be indicated at open
			 * time.
			 */
			fd = open(device, O_RDWR);
			if (fd == -1 && errno == EACCES)
				fd = open(device, O_RDONLY);
		} while (fd < 0 && errno == EBUSY);
	}

	/*
	 * XXX better message for all minors used
	 */
	if (fd < 0) {
		switch (errno) {

		case ENOENT:
			fd = PCAP_ERROR;
			if (n == 1) {
				/*
				 * /dev/bpf0 doesn't exist, which
				 * means we probably have no BPF
				 * devices.
				 */
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "(there are no BPF devices)");
			} else {
				/*
				 * We got EBUSY on at least one
				 * BPF device, so we have BPF
				 * devices, but all the ones
				 * that exist are busy.
				 */
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "(all BPF devices are busy)");
			}
			break;

		case EACCES:
			/*
			 * Got EACCES on the last device we tried,
			 * and EBUSY on all devices before that,
			 * if any.
			 */
			fd = PCAP_ERROR_PERM_DENIED;
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "(cannot open BPF device) %s", device);
			break;

		default:
			/*
			 * Some other problem.
			 */
			fd = PCAP_ERROR;
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "(cannot open BPF device) %s", device);
			break;
		}
	}

	return (fd);
}