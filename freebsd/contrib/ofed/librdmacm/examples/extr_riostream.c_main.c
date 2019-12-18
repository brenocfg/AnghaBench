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
struct TYPE_4__ {int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_socktype; } ;
struct TYPE_3__ {int ai_flags; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_port_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IB ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int MSG_DONTWAIT ; 
 int RAI_FAMILY ; 
 int RAI_NUMERICHOST ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SWITCH_FALLTHROUGH ; 
 TYPE_2__ ai_hints ; 
 void* atoi (void*) ; 
 void* buffer_size ; 
 int custom ; 
 void* dst_addr ; 
 int /*<<< orphan*/  exit (int) ; 
 int flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 void* inline_size ; 
 void* iterations ; 
 void* optarg ; 
 int poll_timeout ; 
 void* port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ rai_hints ; 
 int run () ; 
 int /*<<< orphan*/  set_test_opt (void*) ; 
 int size_option ; 
 void* src_addr ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncasecmp (char*,void*,int) ; 
 void* transfer_count ; 
 void* transfer_size ; 
 int use_rgai ; 

int main(int argc, char **argv)
{
	int op, ret;

	ai_hints.ai_socktype = SOCK_STREAM;
	rai_hints.ai_port_space = RDMA_PS_TCP;
	while ((op = getopt(argc, argv, "s:b:f:B:i:I:C:S:p:T:")) != -1) {
		switch (op) {
		case 's':
			dst_addr = optarg;
			break;
		case 'b':
			src_addr = optarg;
			break;
		case 'f':
			if (!strncasecmp("ip", optarg, 2)) {
				ai_hints.ai_flags = AI_NUMERICHOST;
			} else if (!strncasecmp("gid", optarg, 3)) {
				rai_hints.ai_flags = RAI_NUMERICHOST | RAI_FAMILY;
				rai_hints.ai_family = AF_IB;
				use_rgai = 1;
			} else {
				fprintf(stderr, "Warning: unknown address format\n");
			}
			break;
		case 'B':
			buffer_size = atoi(optarg);
			break;
		case 'i':
			inline_size = atoi(optarg);
			break;
		case 'I':
			custom = 1;
			iterations = atoi(optarg);
			break;
		case 'C':
			custom = 1;
			transfer_count = atoi(optarg);
			break;
		case 'S':
			if (!strncasecmp("all", optarg, 3)) {
				size_option = 1;
			} else {
				custom = 1;
				transfer_size = atoi(optarg);
			}
			break;
		case 'p':
			port = optarg;
			break;
		case 'T':
			if (!set_test_opt(optarg))
				break;
			/* invalid option - fall through */
			SWITCH_FALLTHROUGH;
		default:
			printf("usage: %s\n", argv[0]);
			printf("\t[-s server_address]\n");
			printf("\t[-b bind_address]\n");
			printf("\t[-f address_format]\n");
			printf("\t    name, ip, ipv6, or gid\n");
			printf("\t[-B buffer_size]\n");
			printf("\t[-i inline_size]\n");
			printf("\t[-I iterations]\n");
			printf("\t[-C transfer_count]\n");
			printf("\t[-S transfer_size or all]\n");
			printf("\t[-p port_number]\n");
			printf("\t[-T test_option]\n");
			printf("\t    a|async - asynchronous operation (use poll)\n");
			printf("\t    b|blocking - use blocking calls\n");
			printf("\t    n|nonblocking - use nonblocking calls\n");
			printf("\t    v|verify - verify data\n");
			exit(1);
		}
	}

	if (!(flags & MSG_DONTWAIT))
		poll_timeout = -1;

	ret = run();
	return ret;
}