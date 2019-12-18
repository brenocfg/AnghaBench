#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bpf_program {int bf_len; struct bpf_insn* bf_insns; } ;
struct bpf_insn {int k; int /*<<< orphan*/  jf; int /*<<< orphan*/  jt; int /*<<< orphan*/  code; } ;
struct TYPE_3__ {int fd; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 scalar_t__ get_error_response (int,int /*<<< orphan*/ *) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_to_fd (int,int,unsigned char*) ; 

__attribute__((used)) static int pcap_setfilter_acn(pcap_t *handle, struct bpf_program *bpf) {
	int				fd = handle->fd;
	int				count;
	struct bpf_insn	*p;
	uint16_t		shortInt;
	uint32_t		longInt;

	send_to_fd(fd, 1, (unsigned char *)"F");			/* BPF filter follows command */
	count = bpf->bf_len;
	longInt = htonl(count);
	send_to_fd(fd, 4, (unsigned char *)&longInt);		/* send the instruction sequence count */
	p = bpf->bf_insns;
	while (count--) {									/* followed by the list of instructions */
		shortInt = htons(p->code);
		longInt = htonl(p->k);
		send_to_fd(fd, 2, (unsigned char *)&shortInt);
		send_to_fd(fd, 1, (unsigned char *)&p->jt);
		send_to_fd(fd, 1, (unsigned char *)&p->jf);
		send_to_fd(fd, 4, (unsigned char *)&longInt);
		p++;
	}
	if (get_error_response(fd, NULL))
		return -1;
	return 0;
}