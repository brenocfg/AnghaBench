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
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; void* connects_left; int /*<<< orphan*/  dst_in; struct sockaddr* dst_addr; int /*<<< orphan*/  src_in; struct sockaddr* src_addr; } ;

/* Variables and functions */
 int RDMA_PS_IPOIB ; 
 int RDMA_PS_UDP ; 
 scalar_t__ alloc_nodes () ; 
 void* atoi (void*) ; 
 void* connections ; 
 int /*<<< orphan*/  destroy_nodes () ; 
 void* dst_addr ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int is_sender ; 
 void* message_count ; 
 void* message_size ; 
 void* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port_space ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rdma_create_event_channel () ; 
 int /*<<< orphan*/  rdma_destroy_event_channel (int /*<<< orphan*/ ) ; 
 int run () ; 
 void* src_addr ; 
 int /*<<< orphan*/  strtol (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ test ; 
 int unmapped_addr ; 

int main(int argc, char **argv)
{
	int op, ret;


	while ((op = getopt(argc, argv, "m:M:sb:c:C:S:p:")) != -1) {
		switch (op) {
		case 'm':
			dst_addr = optarg;
			break;
		case 'M':
			unmapped_addr = 1;
			dst_addr = optarg;
			break;
		case 's':
			is_sender = 1;
			break;
		case 'b':
			src_addr = optarg;
			test.src_addr = (struct sockaddr *) &test.src_in;
			break;
		case 'c':
			connections = atoi(optarg);
			break;
		case 'C':
			message_count = atoi(optarg);
			break;
		case 'S':
			message_size = atoi(optarg);
			break;
		case 'p':
			port_space = strtol(optarg, NULL, 0);
			break;
		default:
			printf("usage: %s\n", argv[0]);
			printf("\t-m multicast_address\n");
			printf("\t[-M unmapped_multicast_address]\n"
			       "\t replaces -m and requires -b\n");
			printf("\t[-s(ender)]\n");
			printf("\t[-b bind_address]\n");
			printf("\t[-c connections]\n");
			printf("\t[-C message_count]\n");
			printf("\t[-S message_size]\n");
			printf("\t[-p port_space - %#x for UDP (default), "
			       "%#x for IPOIB]\n", RDMA_PS_UDP, RDMA_PS_IPOIB);
			exit(1);
		}
	}

	if (unmapped_addr && !src_addr) {
		printf("unmapped multicast address requires binding "
			"to source address\n");
		exit(1);
	}

	test.dst_addr = (struct sockaddr *) &test.dst_in;
	test.connects_left = connections;

	test.channel = rdma_create_event_channel();
	if (!test.channel) {
		perror("failed to create event channel");
		exit(1);
	}

	if (alloc_nodes())
		exit(1);

	ret = run();

	printf("test complete\n");
	destroy_nodes();
	rdma_destroy_event_channel(test.channel);

	printf("return status %d\n", ret);
	return ret;
}