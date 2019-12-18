#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
typedef  unsigned char u_char ;
struct pcap_pkthdr {int /*<<< orphan*/  caplen; int /*<<< orphan*/  len; int /*<<< orphan*/  ts; } ;
struct pcap_netfilter {int /*<<< orphan*/  packets_read; int /*<<< orphan*/  packets_nobufs; } ;
struct nlmsghdr {int nlmsg_len; int /*<<< orphan*/  nlmsg_type; } ;
struct nfqnl_msg_packet_hdr {int /*<<< orphan*/  packet_id; } ;
struct nfgenmsg {int /*<<< orphan*/  res_id; } ;
typedef  struct nfattr const nfattr ;
struct TYPE_5__ {int /*<<< orphan*/ * bf_insns; } ;
struct TYPE_6__ {int cc; unsigned char* bp; scalar_t__ linktype; TYPE_1__ fcode; int /*<<< orphan*/  errbuf; scalar_t__ break_loop; scalar_t__ buffer; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  fd; struct pcap_netfilter* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (unsigned char*,struct pcap_pkthdr*,unsigned char const*) ;
typedef  scalar_t__ nftype_t ;

/* Variables and functions */
 scalar_t__ DLT_NFLOG ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOBUFS ; 
 int HDR_LENGTH ; 
 unsigned char* NFA_DATA (struct nfattr const*) ; 
 struct nfattr const* NFA_NEXT (struct nfattr const*,int) ; 
 scalar_t__ NFA_OK (struct nfattr const*,int) ; 
 int /*<<< orphan*/  NFA_PAYLOAD (struct nfattr const*) ; 
 int NFA_TYPE (struct nfattr const*) ; 
 scalar_t__ NFLOG ; 
 struct nfattr const* NFM_NFA (struct nfgenmsg const*) ; 
 scalar_t__ NFNL_MSG_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ NFNL_SUBSYS_ID (int /*<<< orphan*/ ) ; 
 scalar_t__ NFNL_SUBSYS_QUEUE ; 
 scalar_t__ NFNL_SUBSYS_ULOG ; 
#define  NFQA_PACKET_HDR 130 
#define  NFQA_PAYLOAD 129 
 scalar_t__ NFQNL_MSG_PACKET ; 
 scalar_t__ NFQUEUE ; 
#define  NFULA_PAYLOAD 128 
 scalar_t__ NFULNL_MSG_PACKET ; 
 int /*<<< orphan*/  NF_ACCEPT ; 
 int NLMSG_ALIGN (int) ; 
 void* NLMSG_DATA (struct nlmsghdr const*) ; 
 int NLMSG_SPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ OTHER ; 
 int /*<<< orphan*/  PACKET_COUNT_IS_UNLIMITED (int) ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_BREAK ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfqueue_send_verdict (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int recv (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netfilter_read_linux(pcap_t *handle, int max_packets, pcap_handler callback, u_char *user)
{
	struct pcap_netfilter *handlep = handle->priv;
	register u_char *bp, *ep;
	int count = 0;
	int len;

	/*
	 * Has "pcap_breakloop()" been called?
	 */
	if (handle->break_loop) {
		/*
		 * Yes - clear the flag that indicates that it
		 * has, and return PCAP_ERROR_BREAK to indicate
		 * that we were told to break out of the loop.
		 */
		handle->break_loop = 0;
		return PCAP_ERROR_BREAK;
	}
	len = handle->cc;
	if (len == 0) {
		/*
		 * The buffer is empty; refill it.
		 *
		 * We ignore EINTR, as that might just be due to a signal
		 * being delivered - if the signal should interrupt the
		 * loop, the signal handler should call pcap_breakloop()
		 * to set handle->break_loop (we ignore it on other
		 * platforms as well).
		 */
		do {
			len = recv(handle->fd, handle->buffer, handle->bufsize, 0);
			if (handle->break_loop) {
				handle->break_loop = 0;
				return PCAP_ERROR_BREAK;
			}
			if (errno == ENOBUFS)
				handlep->packets_nobufs++;
		} while ((len == -1) && (errno == EINTR || errno == ENOBUFS));

		if (len < 0) {
			pcap_fmt_errmsg_for_errno(handle->errbuf,
			    PCAP_ERRBUF_SIZE, errno, "Can't receive packet");
			return PCAP_ERROR;
		}

		bp = (unsigned char *)handle->buffer;
	} else
		bp = handle->bp;
	ep = bp + len;
	while (bp < ep) {
		const struct nlmsghdr *nlh = (const struct nlmsghdr *) bp;
		uint32_t msg_len;
		nftype_t type = OTHER;
		/*
		 * Has "pcap_breakloop()" been called?
		 * If so, return immediately - if we haven't read any
		 * packets, clear the flag and return PCAP_ERROR_BREAK
		 * to indicate that we were told to break out of the loop,
		 * otherwise leave the flag set, so that the *next* call
		 * will break out of the loop without having read any
		 * packets, and return the number of packets we've
		 * processed so far.
		 */
		if (handle->break_loop) {
			handle->bp = bp;
			handle->cc = ep - bp;
			if (count == 0) {
				handle->break_loop = 0;
				return PCAP_ERROR_BREAK;
			} else
				return count;
		}
		if (ep - bp < NLMSG_SPACE(0)) {
			/*
			 * There's less than one netlink message left
			 * in the buffer.  Give up.
			 */
			break;
		}

		if (nlh->nlmsg_len < sizeof(struct nlmsghdr) || (u_int)len < nlh->nlmsg_len) {
			pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "Message truncated: (got: %d) (nlmsg_len: %u)", len, nlh->nlmsg_len);
			return -1;
		}

		if (NFNL_SUBSYS_ID(nlh->nlmsg_type) == NFNL_SUBSYS_ULOG &&
		    NFNL_MSG_TYPE(nlh->nlmsg_type) == NFULNL_MSG_PACKET)
			type = NFLOG;
		else if (NFNL_SUBSYS_ID(nlh->nlmsg_type) == NFNL_SUBSYS_QUEUE &&
		         NFNL_MSG_TYPE(nlh->nlmsg_type) == NFQNL_MSG_PACKET)
			type = NFQUEUE;

		if (type != OTHER) {
			const unsigned char *payload = NULL;
			struct pcap_pkthdr pkth;

			const struct nfgenmsg *nfg = NULL;
			int id = 0;

			if (handle->linktype != DLT_NFLOG) {
				const struct nfattr *payload_attr = NULL;

				if (nlh->nlmsg_len < HDR_LENGTH) {
					pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "Malformed message: (nlmsg_len: %u)", nlh->nlmsg_len);
					return -1;
				}

				nfg = NLMSG_DATA(nlh);
				if (nlh->nlmsg_len > HDR_LENGTH) {
					struct nfattr *attr = NFM_NFA(nfg);
					int attr_len = nlh->nlmsg_len - NLMSG_ALIGN(HDR_LENGTH);

					while (NFA_OK(attr, attr_len)) {
						if (type == NFQUEUE) {
							switch (NFA_TYPE(attr)) {
								case NFQA_PACKET_HDR:
									{
										const struct nfqnl_msg_packet_hdr *pkt_hdr = (const struct nfqnl_msg_packet_hdr *) NFA_DATA(attr);

										id = ntohl(pkt_hdr->packet_id);
										break;
									}
								case NFQA_PAYLOAD:
									payload_attr = attr;
									break;
							}

						} else if (type == NFLOG) {
							switch (NFA_TYPE(attr)) {
								case NFULA_PAYLOAD:
									payload_attr = attr;
									break;
							}
						}
						attr = NFA_NEXT(attr, attr_len);
					}
				}

				if (payload_attr) {
					payload = NFA_DATA(payload_attr);
					pkth.len = pkth.caplen = NFA_PAYLOAD(payload_attr);
				}

			} else {
				payload = NLMSG_DATA(nlh);
				pkth.caplen = pkth.len = nlh->nlmsg_len-NLMSG_ALIGN(sizeof(struct nlmsghdr));
			}

			if (payload) {
				/* pkth.caplen = min (payload_len, handle->snapshot); */

				gettimeofday(&pkth.ts, NULL);
				if (handle->fcode.bf_insns == NULL ||
						bpf_filter(handle->fcode.bf_insns, payload, pkth.len, pkth.caplen))
				{
					handlep->packets_read++;
					callback(user, &pkth, payload);
					count++;
				}
			}

			if (type == NFQUEUE) {
				/* XXX, possible responses: NF_DROP, NF_ACCEPT, NF_STOLEN, NF_QUEUE, NF_REPEAT, NF_STOP */
				/* if type == NFQUEUE, handle->linktype is always != DLT_NFLOG,
				   so nfg is always initialized to NLMSG_DATA(nlh). */
				if (nfg != NULL)
					nfqueue_send_verdict(handle, ntohs(nfg->res_id), id, NF_ACCEPT);
			}
		}

		msg_len = NLMSG_ALIGN(nlh->nlmsg_len);
		/*
		 * If the message length would run past the end of the
		 * buffer, truncate it to the remaining space in the
		 * buffer.
		 */
		if (msg_len > ep - bp)
			msg_len = ep - bp;

		bp += msg_len;
		if (count >= max_packets && !PACKET_COUNT_IS_UNLIMITED(max_packets)) {
			handle->bp = bp;
			handle->cc = ep - bp;
			if (handle->cc < 0)
				handle->cc = 0;
			return count;
		}
	}

	handle->cc = 0;
	return count;
}