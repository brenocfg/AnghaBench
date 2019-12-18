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
struct TYPE_2__ {int /*<<< orphan*/  ai_qp_type; int /*<<< orphan*/  ai_port_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QPT_RC ; 
 int /*<<< orphan*/  IBV_QPT_XRC_SEND ; 
 int /*<<< orphan*/  RDMA_PS_IB ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 TYPE_1__ hints ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * server ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int test () ; 
 int /*<<< orphan*/  tolower (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	int op, ret;

	hints.ai_port_space = RDMA_PS_TCP;
	hints.ai_qp_type = IBV_QPT_RC;

	while ((op = getopt(argc, argv, "s:p:c:")) != -1) {
		switch (op) {
		case 's':
			server = optarg;
			break;
		case 'p':
			strncpy(port, optarg, sizeof port - 1);
			break;
		case 'c':
			switch (tolower(optarg[0])) {
			case 'r':
				break;
			case 'x':
				hints.ai_port_space = RDMA_PS_IB;
				hints.ai_qp_type = IBV_QPT_XRC_SEND;
				break;
			default:
				goto err;
			}
			break;
		default:
			goto err;
		}
	}

	printf("%s: start\n", argv[0]);
	ret = test();
	printf("%s: end %d\n", argv[0], ret);
	return ret;

err:
	printf("usage: %s\n", argv[0]);
	printf("\t[-s server]\n");
	printf("\t[-p port_number]\n");
	printf("\t[-c communication type]\n");
	printf("\t    r - RC: reliable-connected (default)\n");
	printf("\t    x - XRC: extended-reliable-connected\n");
	exit(1);
}