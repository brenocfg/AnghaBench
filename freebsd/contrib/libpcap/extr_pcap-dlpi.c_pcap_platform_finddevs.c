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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  A_GET_UNITS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_if_flags ; 
 int /*<<< orphan*/  is_dlpi_interface ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pcap_findalldevs_interfaces (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,scalar_t__) ; 
 scalar_t__ strioctl (int,int /*<<< orphan*/ ,int,char*) ; 

int
pcap_platform_finddevs(pcap_if_list_t *devlistp, char *errbuf)
{
#ifdef HAVE_SOLARIS
	int fd;
	union {
		u_int nunits;
		char pad[516];	/* XXX - must be at least 513; is 516
				   in "atmgetunits" */
	} buf;
	char baname[2+1+1];
	u_int i;
#endif

	/*
	 * Get the list of regular interfaces first.
	 */
	if (pcap_findalldevs_interfaces(devlistp, errbuf, is_dlpi_interface,
	    get_if_flags) == -1)
		return (-1);	/* failure */

#ifdef HAVE_SOLARIS
	/*
	 * We may have to do special magic to get ATM devices.
	 */
	if ((fd = open("/dev/ba", O_RDWR)) < 0) {
		/*
		 * We couldn't open the "ba" device.
		 * For now, just give up; perhaps we should
		 * return an error if the problem is neither
		 * a "that device doesn't exist" error (ENOENT,
		 * ENXIO, etc.) or a "you're not allowed to do
		 * that" error (EPERM, EACCES).
		 */
		return (0);
	}

	if (strioctl(fd, A_GET_UNITS, sizeof(buf), (char *)&buf) < 0) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "A_GET_UNITS");
		return (-1);
	}
	for (i = 0; i < buf.nunits; i++) {
		pcap_snprintf(baname, sizeof baname, "ba%u", i);
		/*
		 * XXX - is there a notion of "up" and "running"?
		 * And is there a way to determine whether the
		 * interface is plugged into a network?
		 */
		if (add_dev(devlistp, baname, 0, NULL, errbuf) == NULL)
			return (-1);
	}
#endif

	return (0);
}