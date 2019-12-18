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
struct stat {int /*<<< orphan*/  st_rdev; } ;
struct ifreq {int ifr_mtu; int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 unsigned int IFF_UP ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  TAP_DEV ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  devname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fstat (int,struct stat*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tapdev ; 
 int tapfd ; 
 int /*<<< orphan*/  time_print (char*,int /*<<< orphan*/ ) ; 

void open_tap() {
	struct stat st;
	int s;
	struct ifreq ifr;
	unsigned int flags;
	
	tapfd = open(TAP_DEV, O_RDWR);
	if (tapfd == -1) {
		printf("Can't open tap: %s\n", strerror(errno));
		exit(1);
	}
	if(fstat(tapfd, &st) == -1) {
		perror("fstat()");
		exit(1);
	}

	// feer
	strcpy(tapdev, devname(st.st_rdev, S_IFCHR));

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s == -1) {
		perror("socket()");
		exit(1);
	}
	
	// MTU
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, tapdev);
	ifr.ifr_mtu = 1500;
	if (ioctl(s, SIOCSIFMTU, &ifr) == -1) {
		perror("ioctl(SIOCSIFMTU)");
		exit(1);
	}

	// set iface up
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, tapdev);
	if (ioctl(s, SIOCGIFFLAGS, &ifr) == -1) {
		perror("ioctl(SIOCGIFFLAGS)");
		exit(1);
	}

	flags = (ifr.ifr_flags & 0xffff) | (ifr.ifr_flagshigh << 16);
	flags |= IFF_UP;
	
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, tapdev);
	ifr.ifr_flags = flags & 0xffff;
	ifr.ifr_flagshigh = flags >> 16;
	if (ioctl(s, SIOCSIFFLAGS, &ifr) == -1) {
		perror("ioctl(SIOCSIFFLAGS)");
		exit(1);
	}

	close(s);
	time_print("Opened tap device: %s\n", tapdev);
}