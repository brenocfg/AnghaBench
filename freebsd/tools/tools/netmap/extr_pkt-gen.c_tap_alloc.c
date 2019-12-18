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
struct ifreq {int ifr_flags; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,char*) ; 
 int IFF_NO_PI ; 
 int IFF_TAP ; 
 size_t IFNAMSIZ ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* TAP_CLONEDEV ; 
 int /*<<< orphan*/  TUNSETIFF ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
tap_alloc(char *dev)
{
	struct ifreq ifr;
	int fd, err;
	char *clonedev = TAP_CLONEDEV;

	(void)err;
	(void)dev;
	/* Arguments taken by the function:
	 *
	 * char *dev: the name of an interface (or '\0'). MUST have enough
	 *   space to hold the interface name if '\0' is passed
	 * int flags: interface flags (eg, IFF_TUN etc.)
	 */

#ifdef __FreeBSD__
	if (dev[3]) { /* tapSomething */
		static char buf[128];
		snprintf(buf, sizeof(buf), "/dev/%s", dev);
		clonedev = buf;
	}
#endif
	/* open the device */
	if( (fd = open(clonedev, O_RDWR)) < 0 ) {
		return fd;
	}
	D("%s open successful", clonedev);

	/* preparation of the struct ifr, of type "struct ifreq" */
	memset(&ifr, 0, sizeof(ifr));

#ifdef linux
	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

	if (*dev) {
		/* if a device name was specified, put it in the structure; otherwise,
		* the kernel will try to allocate the "next" device of the
		* specified type */
		size_t len = strlen(dev);
		if (len > IFNAMSIZ) {
			D("%s too long", dev);
			return -1;
		}
		memcpy(ifr.ifr_name, dev, len);
	}

	/* try to create the device */
	if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
		D("failed to to a TUNSETIFF: %s", strerror(errno));
		close(fd);
		return err;
	}

	/* if the operation was successful, write back the name of the
	* interface to the variable "dev", so the caller can know
	* it. Note that the caller MUST reserve space in *dev (see calling
	* code below) */
	strcpy(dev, ifr.ifr_name);
	D("new name is %s", dev);
#endif /* linux */

	/* this is the special file descriptor that the caller will use to talk
	 * with the virtual interface */
	return fd;
}