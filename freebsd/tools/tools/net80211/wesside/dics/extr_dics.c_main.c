#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct pcap_pkthdr {scalar_t__ caplen; } ;
typedef  int /*<<< orphan*/  s_in ;
typedef  int /*<<< orphan*/  rd ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
#define  DLT_EN10MB 129 
#define  DLT_NULL 128 
 int /*<<< orphan*/  DPORT ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_HDRINCL ; 
 int /*<<< orphan*/  IP_RECVTTL ; 
 int PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PF_INET ; 
 unsigned char PRGA_LEN ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 unsigned char TTLSENT ; 
 int atoi (char*) ; 
 int bind (int,struct sockaddr*,int) ; 
 scalar_t__ check_signal (int,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_close (int /*<<< orphan*/ *) ; 
 int pcap_datalink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_next (int /*<<< orphan*/ *,struct pcap_pkthdr*) ; 
 int /*<<< orphan*/ * pcap_open_live (char*,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pps ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_stuff (int,unsigned char*,char*,unsigned short,unsigned char) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int main(int argc, char *argv[]) {
	int s, us;
	int rd = 1;

#if 0	
	const u_char* buf;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr phdr;
	pcap_t* p;
	int dtl;
#endif	

	int got_it = 0;
	char ip[16] = "\x00";
	unsigned char ttl = 0;
	unsigned short port;
	struct sockaddr_in s_in;
	struct timeval tv;
	fd_set rfds;
	unsigned char* sip = 0;

	if (argc < 2) {
		printf("Usage: %s <sip> [pps]\n", argv[0]);
		exit(1);
	}

	if (argc > 2) {
		pps = atoi(argv[2]);
	}

	printf("PPS=%d\n", pps);

	sip = argv[1];

	memset(&s_in, 0, sizeof(s_in));
	us = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == -1) {
		perror("socket()");
		exit(1);
	}
	s_in.sin_family = PF_INET;
	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_port = htons(DPORT);
	if (bind (us, (struct sockaddr*)&s_in, sizeof(s_in)) == -1) {
		perror("bind()");
		exit(1);
	}

	rd = 1;
	if (setsockopt(us, IPPROTO_IP, IP_RECVTTL, &rd, sizeof(rd)) == -1) {
		perror("setsockopt()");
		exit(1);
	}

	s = socket (PF_INET, SOCK_RAW, IPPROTO_UDP);
	if (s == -1) {
		perror("socket()");
		exit(1);
	}
	
	rd = 1;
	if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &rd, sizeof(rd)) == -1) {
		perror("setsockopt()");
		exit(1);
	}


#if 0
        p = pcap_open_live(argv[1], 512, 0, 25, errbuf);
	if (!p) {
		printf("pcap_open_live(): %s\n", errbuf);
		exit(1);
	}
	
	dtl = pcap_datalink(p);

	switch (dtl) {
		case DLT_NULL:
			dtl = 4;
			break;

		case DLT_EN10MB:
			dtl = 14;
			break;

		default:
			printf("Unknown datalink %d\n", dtl);
			exit(1);
	}

	printf("Datalink size=%d\n", dtl);
#endif
	while (1) {
#if 0	
		buf = pcap_next(p, &phdr);
		if (buf) {
			if (check_signal(buf+dtl, phdr.caplen-dtl, 
					 ip, &ttl, &port)) {
				got_it = 2;
				printf("Got signal from %s:%d TTL=%d\n", 
				       ip, port, ttl);
			}	
		}
#endif
		FD_ZERO(&rfds);
		FD_SET(us, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = 10*1000;
		rd = select(us+1, &rfds, NULL, NULL, &tv);
		if (rd == -1) {
			perror("select()");
			exit(1);
		}
		if (rd == 1 && FD_ISSET(us, &rfds)) {
			char ipnew[16];
			unsigned char ttlnew;
			if (check_signal(us, ipnew, &ttlnew, &port)) {
				int send_ttl = 0;
				if (ttlnew != ttl || strcmp(ipnew, ip) != 0 ||
				    got_it == 0) {
				    	send_ttl = 1;
				}	
				ttl = ttlnew;
				strcpy(ip, ipnew);
				
				printf("Got signal from %s:%d TTL=%d\n", 
				       ip, port, ttl);
				got_it = 2;
				
				if (send_ttl) {
					printf("Sending ttl (%d)...\n", ttl);
					send_stuff(s, sip, ip, port, 69 + (TTLSENT-ttl));
				}	
			}	
		}

		if (got_it) {
			printf("Sending stuff to %s...\n", ip);
			send_stuff(s, sip, ip, port, PRGA_LEN);
			got_it--;

			if (got_it == 0) {
				printf("Stopping send\n");
			}
		}
	}

#if 0
	pcap_close(p);
#endif

	close(s);
	close(us);
	exit(0);
}