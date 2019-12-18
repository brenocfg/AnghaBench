#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_family; } ;
struct ifreq {char* ifr_name; int ifr_flags; TYPE_1__ ifr_addr; } ;
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  pidfile ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_6__ {int /*<<< orphan*/ * pfh; int /*<<< orphan*/  state; int /*<<< orphan*/  laddr; int /*<<< orphan*/  raddr; scalar_t__ mru; int /*<<< orphan*/  recv; int /*<<< orphan*/  send; } ;
typedef  TYPE_2__ channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_LINK ; 
 int /*<<< orphan*/  CHANNEL_OPEN ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_MAX_LEN ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int IFF_UP ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFLLADDR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TAPGIFNAME ; 
 char* _PATH_VARRUN ; 
 int /*<<< orphan*/  b2eaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* channel_alloc () ; 
 int /*<<< orphan*/  channel_open (TYPE_2__*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_name ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  local_bdaddr ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_info (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pidfile_open (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ pidfile_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_recv ; 
 int /*<<< orphan*/  tap_send ; 

void
tap_init(void)
{
	channel_t *chan;
	struct ifreq ifr;
	int fd, s;
	char pidfile[PATH_MAX];

	fd = open(interface_name, O_RDWR);
	if (fd == -1) {
		log_err("Could not open \"%s\": %m", interface_name);
		exit(EXIT_FAILURE);
	}

	memset(&ifr, 0, sizeof(ifr));
	if (ioctl(fd, TAPGIFNAME, &ifr) == -1) {
		log_err("Could not get interface name: %m");
		exit(EXIT_FAILURE);
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1) {
		log_err("Could not open PF_LINK socket: %m");
		exit(EXIT_FAILURE);
	}

	ifr.ifr_addr.sa_family = AF_LINK;
	ifr.ifr_addr.sa_len = ETHER_ADDR_LEN;
	b2eaddr(ifr.ifr_addr.sa_data, &local_bdaddr);

	if (ioctl(s, SIOCSIFLLADDR, &ifr) == -1) {
		log_err("Could not set %s physical address: %m", ifr.ifr_name);
		exit(EXIT_FAILURE);
	}

	if (ioctl(s, SIOCGIFFLAGS, &ifr) == -1) {
		log_err("Could not get interface flags: %m");
		exit(EXIT_FAILURE);
	}

	if ((ifr.ifr_flags & IFF_UP) == 0) {
		ifr.ifr_flags |= IFF_UP;

		if (ioctl(s, SIOCSIFFLAGS, &ifr) == -1) {
			log_err("Could not set IFF_UP: %m");
			exit(EXIT_FAILURE);
		}
	}

	close(s);

	log_info("Using interface %s with addr %s", ifr.ifr_name,
		ether_ntoa((struct ether_addr *)&ifr.ifr_addr.sa_data));

	chan = channel_alloc();
	if (chan == NULL)
		exit(EXIT_FAILURE);

	chan->send = tap_send;
	chan->recv = tap_recv;
	chan->mru = ETHER_HDR_LEN + ETHER_MAX_LEN;
	memcpy(chan->raddr, ifr.ifr_addr.sa_data, ETHER_ADDR_LEN);
	memcpy(chan->laddr, ifr.ifr_addr.sa_data, ETHER_ADDR_LEN);
	chan->state = CHANNEL_OPEN;
	if (!channel_open(chan, fd))
		exit(EXIT_FAILURE);

	snprintf(pidfile, sizeof(pidfile), "%s/%s.pid",
		_PATH_VARRUN, ifr.ifr_name);
	chan->pfh = pidfile_open(pidfile, 0600, NULL);
	if (chan->pfh == NULL)
		log_err("can't create pidfile");
	else if (pidfile_write(chan->pfh) < 0) {
		log_err("can't write pidfile");
		pidfile_remove(chan->pfh);
		chan->pfh = NULL;
	}
}