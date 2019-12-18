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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_USB_MON_DEV ; 
 int PATH_MAX ; 
 char* PROC_USB_BUS_DIR ; 
 char* SYS_USB_BUS_DIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ have_binary_usbmon () ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int usb_dev_add (int /*<<< orphan*/ *,int,char*) ; 

int
usb_findalldevs(pcap_if_list_t *devlistp, char *err_str)
{
	char usb_mon_dir[PATH_MAX];
	char *usb_mon_prefix;
	size_t usb_mon_prefix_len;
	struct dirent* data;
	int ret = 0;
	DIR* dir;
	int n;
	char* name;
	size_t len;

	if (have_binary_usbmon()) {
		/*
		 * We have binary-mode support.
		 * What do the device names look like?
		 * Split LINUX_USB_MON_DEV into a directory that we'll
		 * scan and a file name prefix that we'll check for.
		 */
		strlcpy(usb_mon_dir, LINUX_USB_MON_DEV, sizeof usb_mon_dir);
		usb_mon_prefix = strrchr(usb_mon_dir, '/');
		if (usb_mon_prefix == NULL) {
			/*
			 * This "shouldn't happen".  Just give up if it
			 * does.
			 */
			return 0;
		}
		*usb_mon_prefix++ = '\0';
		usb_mon_prefix_len = strlen(usb_mon_prefix);

		/*
		 * Open the directory and scan it.
		 */
		dir = opendir(usb_mon_dir);
		if (dir != NULL) {
			while ((ret == 0) && ((data = readdir(dir)) != 0)) {
				name = data->d_name;

				/*
				 * Is this a usbmon device?
				 */
				if (strncmp(name, usb_mon_prefix, usb_mon_prefix_len) != 0)
					continue;	/* no */

				/*
				 * What's the device number?
				 */
				if (sscanf(&name[usb_mon_prefix_len], "%d", &n) == 0)
					continue;	/* failed */

				ret = usb_dev_add(devlistp, n, err_str);
			}

			closedir(dir);
		}
		return 0;
	} else {
		/*
		 * We have only text mode support.
		 * We don't look for the text devices because we can't
		 * look for them without root privileges, and we don't
		 * want to require root privileges to enumerate devices
		 * (we want to let the user to try a device and get
		 * an error, rather than seeing no devices and asking
		 * "why am I not seeing devices" and forcing a long
		 * process of poking to figure out whether it's "no
		 * privileges" or "your kernel is too old" or "the
		 * usbmon module isn't loaded" or...).
		 *
		 * Instead, we look to see what buses we have.
		 * If the kernel is so old that it doesn't have
		 * binary-mode support, it's also so old that
		 * it doesn't have a "scan all buses" device.
		 *
		 * First, try scanning sysfs USB bus directory.
		 */
		dir = opendir(SYS_USB_BUS_DIR);
		if (dir != NULL) {
			while ((ret == 0) && ((data = readdir(dir)) != 0)) {
				name = data->d_name;

				if (strncmp(name, "usb", 3) != 0)
					continue;

				if (sscanf(&name[3], "%d", &n) == 0)
					continue;

				ret = usb_dev_add(devlistp, n, err_str);
			}

			closedir(dir);
			return 0;
		}

		/* That didn't work; try scanning procfs USB bus directory. */
		dir = opendir(PROC_USB_BUS_DIR);
		if (dir != NULL) {
			while ((ret == 0) && ((data = readdir(dir)) != 0)) {
				name = data->d_name;
				len = strlen(name);

				/* if this file name does not end with a number it's not of our interest */
				if ((len < 1) || !isdigit(name[--len]))
					continue;
				while (isdigit(name[--len]));
				if (sscanf(&name[len+1], "%d", &n) != 1)
					continue;

				ret = usb_dev_add(devlistp, n, err_str);
			}

			closedir(dir);
			return ret;
		}

		/* neither of them worked */
		return 0;
	}
}