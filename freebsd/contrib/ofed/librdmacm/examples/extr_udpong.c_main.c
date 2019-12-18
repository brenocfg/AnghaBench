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
 int CTRL_MSG_SIZE ; 
 int /*<<< orphan*/  SWITCH_FALLTHROUGH ; 
 void* atoi (void*) ; 
 void* buffer_size ; 
 int client_run () ; 
 int custom ; 
 void* dst_addr ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ flags ; 
 int getopt (int,char**,char*) ; 
 void* optarg ; 
 int poll_timeout ; 
 void* port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_test_opt (void*) ; 
 void* src_addr ; 
 int svr_run () ; 
 void* transfer_count ; 
 int transfer_size ; 

int main(int argc, char **argv)
{
	int op, ret;

	while ((op = getopt(argc, argv, "s:b:B:C:S:p:T:")) != -1) {
		switch (op) {
		case 's':
			dst_addr = optarg;
			break;
		case 'b':
			src_addr = optarg;
			break;
		case 'B':
			buffer_size = atoi(optarg);
			break;
		case 'C':
			custom = 1;
			transfer_count = atoi(optarg);
			break;
		case 'S':
			custom = 1;
			transfer_size = atoi(optarg);
			if (transfer_size < CTRL_MSG_SIZE) {
				printf("size must be at least %d bytes\n",
				       CTRL_MSG_SIZE);
				exit(1);
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
			printf("\t[-B buffer_size]\n");
			printf("\t[-C transfer_count]\n");
			printf("\t[-S transfer_size]\n");
			printf("\t[-p port_number]\n");
			printf("\t[-T test_option]\n");
			printf("\t    s|sockets - use standard tcp/ip sockets\n");
			printf("\t    a|async - asynchronous operation (use poll)\n");
			printf("\t    b|blocking - use blocking calls\n");
			printf("\t    n|nonblocking - use nonblocking calls\n");
			printf("\t    e|echo - server echoes all messages\n");
			exit(1);
		}
	}

	if (flags)
		poll_timeout = -1;

	ret = dst_addr ? client_run() : svr_run();
	return ret;
}