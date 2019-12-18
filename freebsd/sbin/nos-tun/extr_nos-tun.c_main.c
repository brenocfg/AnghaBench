#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wherefrom ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct ip {int ip_hl; TYPE_1__ ip_src; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Finish (int) ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ Set_address (char*,struct sockaddr_in*) ; 
 int atoi (char*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int net ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int read (int,char*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int)) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int tun ; 
 scalar_t__ tun_open (char*,struct sockaddr*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

int main (int argc, char **argv)
{
  int  c, len, ipoff;

  char *dev_name = NULL;
  char *point_to = NULL;
  char *to_point = NULL;
  char *target;
  char *source = NULL;
  char *protocol = NULL;
  int protnum;

  struct sockaddr t_laddr;          /* Source address of tunnel */
  struct sockaddr whereto;          /* Destination of tunnel */
  struct sockaddr wherefrom;        /* Source of tunnel */
  struct sockaddr_in *to;

  char buf[0x2000];                 /* Packets buffer */
  struct ip *ip = (struct ip *)buf;

  fd_set rfds;                      /* File descriptors for select() */
  int nfds;                         /* Return from select() */
  int lastfd;                       /* highest fd we care about */


  while ((c = getopt(argc, argv, "d:s:t:p:")) != -1) {
    switch (c) {
    case 'd':
      to_point = optarg;
      break;
    case 's':
      point_to = optarg;
      break;
    case 't':
      dev_name = optarg;
      break;
    case 'p':
      protocol = optarg;
      break;
    }
  }
  argc -= optind;
  argv += optind;

  if ((argc != 1 && argc != 2) || (dev_name == NULL) ||
      (point_to == NULL) || (to_point == NULL)) {
    usage();
  }

  if(protocol == NULL)
      protnum = 94;
  else
      protnum = atoi(protocol);

  if (argc == 1) {
      target = *argv;
  } else {
      source = *argv++; target = *argv;
  }

  /* Establish logging through 'syslog' */
  openlog("nos-tun", LOG_PID, LOG_DAEMON);

  if(Set_address(point_to, (struct sockaddr_in *)&t_laddr)) {
    closelog();
    exit(2);
  }

  if(tun_open(dev_name, &t_laddr, to_point)) {
    closelog();
    exit(3);
  }

  to = (struct sockaddr_in *)&whereto;
  if(Set_address(target, to))
    Finish(4);

  if ((net = socket(AF_INET, SOCK_RAW, protnum)) < 0) {
    syslog(LOG_ERR,"can't open socket - %m");
    Finish(5);
  }

  if (source) { 
	if (Set_address(source, (struct sockaddr_in *)&wherefrom))
	  Finish(9);
    if (bind(net, &wherefrom, sizeof(wherefrom)) < 0) {
	  syslog(LOG_ERR, "can't bind source address - %m");
	  Finish(10);
	}
  }

  if (connect(net,&whereto,sizeof(struct sockaddr_in)) < 0 ) {
    syslog(LOG_ERR,"can't connect to target - %m");
    close(net);
    Finish(6);
  }

  /*  Demonize it */
  daemon(0,0);

  /* Install signal handlers */
  (void)signal(SIGHUP,Finish);
  (void)signal(SIGINT,Finish);
  (void)signal(SIGTERM,Finish);

  if (tun > net)
	lastfd = tun;
  else
	lastfd = net;

  for (;;) {
    /* Set file descriptors for select() */
    FD_ZERO(&rfds);
    FD_SET(tun,&rfds); FD_SET(net,&rfds);

    nfds = select(lastfd+1,&rfds,NULL,NULL,NULL);
    if(nfds < 0) {
      syslog(LOG_ERR,"interrupted select");
      close(net);
      Finish(7);
    }
    if(nfds == 0) {         /* Impossible ? */
      syslog(LOG_ERR,"timeout in select");
      close(net);
      Finish(8);
    }


    if(FD_ISSET(net,&rfds)) {
      /* Read from socket ... */
      len = read(net, buf, sizeof(buf));
      /* Check if this is "our" packet */
      if((ip->ip_src).s_addr == (to->sin_addr).s_addr) {
	/* ... skip encapsulation headers ... */
	ipoff = (ip->ip_hl << 2);
	/* ... and write to tun-device */
	write(tun,buf+ipoff,len-ipoff);
      }
    }

    if(FD_ISSET(tun,&rfds)) {
      /* Read from tun ... */
      len = read(tun, buf, sizeof(buf));
      /* ... and send to network */
      if(send(net, buf, len,0) <= 0) {
	syslog(LOG_ERR,"can't send - %m");
      }
    }
  }
}