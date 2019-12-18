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
struct nl_classifier_instance {int /*<<< orphan*/  sock; int /*<<< orphan*/  stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  nl_classifier_exit (struct nl_classifier_instance*) ; 
 int nl_classifier_init (struct nl_classifier_instance*) ; 
 int /*<<< orphan*/  nl_classifier_offload (struct nl_classifier_instance*,unsigned char,unsigned long*,unsigned long*,unsigned short,unsigned short,int) ; 
 int nl_classifier_parse_arg (int,char**,unsigned char*,unsigned long*,unsigned long*,unsigned short*,unsigned short*,int*) ; 
 struct nl_classifier_instance nl_cls_inst ; 
 int /*<<< orphan*/  nl_recvmsgs_default (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[])
{
	struct nl_classifier_instance *inst = &nl_cls_inst;
	unsigned char proto;
	unsigned long src_addr[4];
	unsigned long dst_addr[4];
	unsigned short sport;
	unsigned short dport;
	int af;
	int ret;

	ret = nl_classifier_parse_arg(argc, argv, &proto, src_addr, dst_addr, &sport, &dport, &af);
	if (ret < 0) {
		printf("Failed to parse arguments\n");
		return ret;
	}

	ret = nl_classifier_init(inst);
	if (ret < 0) {
		printf("Unable to init generic netlink\n");
		return ret;
	}

	nl_classifier_offload(inst, proto, src_addr, dst_addr, sport, dport, af);

	/* main loop to listen on message */
	while (!inst->stop) {
		nl_recvmsgs_default(inst->sock);
	}

	nl_classifier_exit(inst);

	return 0;
}