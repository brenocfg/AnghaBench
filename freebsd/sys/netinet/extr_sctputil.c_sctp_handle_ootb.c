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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr {int dummy; } ;
struct sctphdr {int dummy; } ;
struct sctp_inpcb {int sctp_flags; int /*<<< orphan*/  sctp_asoc_list; } ;
struct sctp_chunkhdr {int chunk_type; int /*<<< orphan*/  chunk_length; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
#define  SCTP_ABORT_ASSOCIATION 132 
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CALLED_DIRECTLY_NOCMPSET ; 
 int /*<<< orphan*/  SCTP_FREE_SHOULD_USE_ABORT ; 
#define  SCTP_INIT 131 
#define  SCTP_PACKET_DROPPED 130 
 int SCTP_PCB_FLAGS_SOCKET_GONE ; 
#define  SCTP_SHUTDOWN_ACK 129 
#define  SCTP_SHUTDOWN_COMPLETE 128 
 scalar_t__ SCTP_SIZE32 (unsigned int) ; 
 int /*<<< orphan*/  SCTP_STAT_INCR_COUNTER32 (int /*<<< orphan*/ ) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_blackhole ; 
 int /*<<< orphan*/  sctp_inpcb_free (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_m_getptr (struct mbuf*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_send_abort (struct mbuf*,int,struct sockaddr*,struct sockaddr*,struct sctphdr*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_send_shutdown_complete2 (struct sockaddr*,struct sockaddr*,struct sctphdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctps_outoftheblue ; 

void
sctp_handle_ootb(struct mbuf *m, int iphlen, int offset,
    struct sockaddr *src, struct sockaddr *dst,
    struct sctphdr *sh, struct sctp_inpcb *inp,
    struct mbuf *cause,
    uint8_t mflowtype, uint32_t mflowid, uint16_t fibnum,
    uint32_t vrf_id, uint16_t port)
{
	struct sctp_chunkhdr *ch, chunk_buf;
	unsigned int chk_length;
	int contains_init_chunk;

	SCTP_STAT_INCR_COUNTER32(sctps_outoftheblue);
	/* Generate a TO address for future reference */
	if (inp && (inp->sctp_flags & SCTP_PCB_FLAGS_SOCKET_GONE)) {
		if (LIST_EMPTY(&inp->sctp_asoc_list)) {
			sctp_inpcb_free(inp, SCTP_FREE_SHOULD_USE_ABORT,
			    SCTP_CALLED_DIRECTLY_NOCMPSET);
		}
	}
	contains_init_chunk = 0;
	ch = (struct sctp_chunkhdr *)sctp_m_getptr(m, offset,
	    sizeof(*ch), (uint8_t *)&chunk_buf);
	while (ch != NULL) {
		chk_length = ntohs(ch->chunk_length);
		if (chk_length < sizeof(*ch)) {
			/* break to abort land */
			break;
		}
		switch (ch->chunk_type) {
		case SCTP_INIT:
			contains_init_chunk = 1;
			break;
		case SCTP_PACKET_DROPPED:
			/* we don't respond to pkt-dropped */
			return;
		case SCTP_ABORT_ASSOCIATION:
			/* we don't respond with an ABORT to an ABORT */
			return;
		case SCTP_SHUTDOWN_COMPLETE:
			/*
			 * we ignore it since we are not waiting for it and
			 * peer is gone
			 */
			return;
		case SCTP_SHUTDOWN_ACK:
			sctp_send_shutdown_complete2(src, dst, sh,
			    mflowtype, mflowid, fibnum,
			    vrf_id, port);
			return;
		default:
			break;
		}
		offset += SCTP_SIZE32(chk_length);
		ch = (struct sctp_chunkhdr *)sctp_m_getptr(m, offset,
		    sizeof(*ch), (uint8_t *)&chunk_buf);
	}
	if ((SCTP_BASE_SYSCTL(sctp_blackhole) == 0) ||
	    ((SCTP_BASE_SYSCTL(sctp_blackhole) == 1) &&
	    (contains_init_chunk == 0))) {
		sctp_send_abort(m, iphlen, src, dst, sh, 0, cause,
		    mflowtype, mflowid, fibnum,
		    vrf_id, port);
	}
}