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
 int AF_INET ; 
 int AF_INET6 ; 
 unsigned char IPPROTO_TCP ; 
 unsigned char IPPROTO_UDP ; 
 unsigned short htons (unsigned short) ; 
 int inet_pton (int,char*,unsigned long*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 unsigned short strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int nl_classifier_parse_arg(int argc, char *argv[], unsigned char *proto, unsigned long *src_saddr,
			    unsigned long *dst_saddr, unsigned short *sport, unsigned short *dport, int *af)
{
	int ret;
	unsigned short port;

	if (argc < 7) {
		printf("help: nl_classifier <v4|v6> <udp|tcp> <source ip> <destination ip> <source port> <destination port>\n");
		return -1;
	}

	if (0 == strncmp(argv[1], "v4", 2)) {
		*af = AF_INET;
	} else if (0 == strncmp(argv[1], "v6", 2)) {
		*af = AF_INET6;
	} else {
		printf("Address family is not supported");
		return -1;
	}

	if (0 == strncmp(argv[2], "udp", 3)) {
		*proto = IPPROTO_UDP;
	} else if (0 == strncmp(argv[2], "tcp", 3)) {
		*proto = IPPROTO_TCP;
	} else {
		printf("Protocol is not supported");
		return -1;
	}

	ret = inet_pton(*af, argv[3], src_saddr);
	if (ret <= 0) {
		printf("source ip has wrong format\n");
		return -1;
	}

	ret = inet_pton(*af, argv[4], dst_saddr);
	if (ret <= 0) {
		printf("destination ip has wrong format\n");
		return -1;
	}

	port = strtol(argv[5], NULL, 0);
	*sport = htons(port);
	port = strtol(argv[6], NULL, 0);
	*dport = htons(port);

	printf("nl classifier parse arguments successful\n");
	return 0;
}