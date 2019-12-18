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
struct ifreq {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  device ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOCGETIF ; 
 int /*<<< orphan*/  BIOCSETIF ; 
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pcap_fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int write (int,void const*,size_t) ; 

int
pcap_inject(pcap_t *p, const void *buf, size_t len)
{
	int			fd;
	int			res, n = 0;
	char			device[sizeof "/dev/bpf0000000000"];
	struct ifreq		ifr;

        /*
         * Go through all the minors and find one that isn't in use.
         */
	do {
		(void)snprintf(device, sizeof(device), "/dev/bpf%d", n++);
		fd = open(device, O_RDWR);
	} while (fd < 0 && errno == EBUSY);

	if (fd == -1)
		return(-1);

	bzero((char *)&ifr, sizeof(ifr));
	ioctl(pcap_fileno(p), BIOCGETIF, (caddr_t)&ifr);
	ioctl(fd, BIOCSETIF, (caddr_t)&ifr);

	res = write(fd, buf, len);

	close(fd);

	return(res);
}