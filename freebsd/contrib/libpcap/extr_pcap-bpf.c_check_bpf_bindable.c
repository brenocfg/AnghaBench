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

/* Variables and functions */
 int PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int bpf_open_and_bind (char const*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
check_bpf_bindable(const char *name)
{
	int fd;
	char errbuf[PCAP_ERRBUF_SIZE];

	/*
	 * On macOS, we don't do this check if the device name begins
	 * with "wlt"; at least some versions of macOS (actually, it
	 * was called "Mac OS X" then...) offer monitor mode capturing
	 * by having a separate "monitor mode" device for each wireless
	 * adapter, rather than by implementing the ioctls that
	 * {Free,Net,Open,DragonFly}BSD provide. Opening that device
	 * puts the adapter into monitor mode, which, at least for
	 * some adapters, causes them to deassociate from the network
	 * with which they're associated.
	 *
	 * Instead, we try to open the corresponding "en" device (so
	 * that we don't end up with, for users without sufficient
	 * privilege to open capture devices, a list of adapters that
	 * only includes the wlt devices).
	 */
#ifdef __APPLE__
	if (strncmp(name, "wlt", 3) == 0) {
		char *en_name;
		size_t en_name_len;

		/*
		 * Try to allocate a buffer for the "en"
		 * device's name.
		 */
		en_name_len = strlen(name) - 1;
		en_name = malloc(en_name_len + 1);
		if (en_name == NULL) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			return (-1);
		}
		strcpy(en_name, "en");
		strcat(en_name, name + 3);
		fd = bpf_open_and_bind(en_name, errbuf);
		free(en_name);
	} else
#endif /* __APPLE */
	fd = bpf_open_and_bind(name, errbuf);
	if (fd < 0) {
		/*
		 * Error - was it PCAP_ERROR_NO_SUCH_DEVICE?
		 */
		if (fd == PCAP_ERROR_NO_SUCH_DEVICE) {
			/*
			 * Yes, so we can't bind to this because it's
			 * not something supported by BPF.
			 */
			return (0);
		}
		/*
		 * No, so we don't know whether it's supported or not;
		 * say it is, so that the user can at least try to
		 * open it and report the error (which is probably
		 * "you don't have permission to open BPF devices";
		 * reporting those interfaces means users will ask
		 * "why am I getting a permissions error when I try
		 * to capture" rather than "why am I not seeing any
		 * interfaces", making the underlying problem clearer).
		 */
		return (1);
	}

	/*
	 * Success.
	 */
	close(fd);
	return (1);
}