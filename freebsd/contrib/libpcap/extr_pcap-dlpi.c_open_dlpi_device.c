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
typedef  int /*<<< orphan*/  dname ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCAP_DEV_PREFIX ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int get_dlpi_ppa (int,char*,scalar_t__,scalar_t__*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,char const*,...) ; 
 char* split_dname (char*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
open_dlpi_device(const char *name, u_int *ppa, char *errbuf)
{
	int status;
	char dname[100];
	char *cp;
	int fd;
#ifdef HAVE_DEV_DLPI
	u_int unit;
#else
	char dname2[100];
#endif

#ifdef HAVE_DEV_DLPI
	/*
	** Remove any "/dev/" on the front of the device.
	*/
	cp = strrchr(name, '/');
	if (cp == NULL)
		strlcpy(dname, name, sizeof(dname));
	else
		strlcpy(dname, cp + 1, sizeof(dname));

	/*
	 * Split the device name into a device type name and a unit number;
	 * chop off the unit number, so "dname" is just a device type name.
	 */
	cp = split_dname(dname, &unit, errbuf);
	if (cp == NULL)
		return (PCAP_ERROR_NO_SUCH_DEVICE);
	*cp = '\0';

	/*
	 * Use "/dev/dlpi" as the device.
	 *
	 * XXX - HP's DLPI Programmer's Guide for HP-UX 11.00 says that
	 * the "dl_mjr_num" field is for the "major number of interface
	 * driver"; that's the major of "/dev/dlpi" on the system on
	 * which I tried this, but there may be DLPI devices that
	 * use a different driver, in which case we may need to
	 * search "/dev" for the appropriate device with that major
	 * device number, rather than hardwiring "/dev/dlpi".
	 */
	cp = "/dev/dlpi";
	if ((fd = open(cp, O_RDWR)) < 0) {
		if (errno == EPERM || errno == EACCES)
			status = PCAP_ERROR_PERM_DENIED;
		else
			status = PCAP_ERROR;
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "%s", cp);
		return (status);
	}

	/*
	 * Get a table of all PPAs for that device, and search that
	 * table for the specified device type name and unit number.
	 */
	status = get_dlpi_ppa(fd, dname, unit, ppa, errbuf);
	if (status < 0) {
		close(fd);
		return (status);
	}
#else
	/*
	 * If the device name begins with "/", assume it begins with
	 * the pathname of the directory containing the device to open;
	 * otherwise, concatenate the device directory name and the
	 * device name.
	 */
	if (*name == '/')
		strlcpy(dname, name, sizeof(dname));
	else
		pcap_snprintf(dname, sizeof(dname), "%s/%s", PCAP_DEV_PREFIX,
		    name);

	/*
	 * Get the unit number, and a pointer to the end of the device
	 * type name.
	 */
	cp = split_dname(dname, ppa, errbuf);
	if (cp == NULL)
		return (PCAP_ERROR_NO_SUCH_DEVICE);

	/*
	 * Make a copy of the device pathname, and then remove the unit
	 * number from the device pathname.
	 */
	strlcpy(dname2, dname, sizeof(dname));
	*cp = '\0';

	/* Try device without unit number */
	if ((fd = open(dname, O_RDWR)) < 0) {
		if (errno != ENOENT) {
			if (errno == EPERM || errno == EACCES)
				status = PCAP_ERROR_PERM_DENIED;
			else
				status = PCAP_ERROR;
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "%s", dname);
			return (status);
		}

		/* Try again with unit number */
		if ((fd = open(dname2, O_RDWR)) < 0) {
			if (errno == ENOENT) {
				status = PCAP_ERROR_NO_SUCH_DEVICE;

				/*
				 * We provide an error message even
				 * for this error, for diagnostic
				 * purposes (so that, for example,
				 * the app can show the message if the
				 * user requests it).
				 *
				 * In it, we just report "No DLPI device
				 * found" with the device name, so people
				 * don't get confused and think, for example,
				 * that if they can't capture on "lo0"
				 * on Solaris prior to Solaris 11 the fix
				 * is to change libpcap (or the application
				 * that uses it) to look for something other
				 * than "/dev/lo0", as the fix is to use
				 * Solaris 11 or some operating system
				 * other than Solaris - you just *can't*
				 * capture on a loopback interface
				 * on Solaris prior to Solaris 11, the lack
				 * of a DLPI device for the loopback
				 * interface is just a symptom of that
				 * inability.
				 */
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "%s: No DLPI device found", name);
			} else {
				if (errno == EPERM || errno == EACCES)
					status = PCAP_ERROR_PERM_DENIED;
				else
					status = PCAP_ERROR;
				pcap_fmt_errmsg_for_errno(errbuf,
				    PCAP_ERRBUF_SIZE, errno, "%s", dname2);
			}
			return (status);
		}
		/* XXX Assume unit zero */
		*ppa = 0;
	}
#endif
	return (fd);
}