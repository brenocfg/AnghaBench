#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpcap_filterbpf_insn {void* k; int /*<<< orphan*/  jt; int /*<<< orphan*/  jf; void* code; } ;
struct rpcap_filter {void* nitems; void* filtertype; } ;
struct bpf_program {int bf_len; struct bpf_insn* bf_insns; } ;
struct bpf_insn {int /*<<< orphan*/  k; int /*<<< orphan*/  jt; int /*<<< orphan*/  jf; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  RPCAP_NETBUF_SIZE ; 
 int /*<<< orphan*/  RPCAP_UPDATEFILTER_BPF ; 
 int /*<<< orphan*/  SOCKBUF_CHECKONLY ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int pcap_compile (TYPE_1__*,struct bpf_program*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_bufferize (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_pack_bpffilter(pcap_t *fp, char *sendbuf, int *sendbufidx, struct bpf_program *prog)
{
	struct rpcap_filter *filter;
	struct rpcap_filterbpf_insn *insn;
	struct bpf_insn *bf_insn;
	struct bpf_program fake_prog;		/* To be used just in case the user forgot to set a filter */
	unsigned int i;

	if (prog->bf_len == 0)	/* No filters have been specified; so, let's apply a "fake" filter */
	{
		if (pcap_compile(fp, &fake_prog, NULL /* buffer */, 1, 0) == -1)
			return -1;

		prog = &fake_prog;
	}

	filter = (struct rpcap_filter *) sendbuf;

	if (sock_bufferize(NULL, sizeof(struct rpcap_filter), NULL, sendbufidx,
		RPCAP_NETBUF_SIZE, SOCKBUF_CHECKONLY, fp->errbuf, PCAP_ERRBUF_SIZE))
		return -1;

	filter->filtertype = htons(RPCAP_UPDATEFILTER_BPF);
	filter->nitems = htonl((int32)prog->bf_len);

	if (sock_bufferize(NULL, prog->bf_len * sizeof(struct rpcap_filterbpf_insn),
		NULL, sendbufidx, RPCAP_NETBUF_SIZE, SOCKBUF_CHECKONLY, fp->errbuf, PCAP_ERRBUF_SIZE))
		return -1;

	insn = (struct rpcap_filterbpf_insn *) (filter + 1);
	bf_insn = prog->bf_insns;

	for (i = 0; i < prog->bf_len; i++)
	{
		insn->code = htons(bf_insn->code);
		insn->jf = bf_insn->jf;
		insn->jt = bf_insn->jt;
		insn->k = htonl(bf_insn->k);

		insn++;
		bf_insn++;
	}

	return 0;
}