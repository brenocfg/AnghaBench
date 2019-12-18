#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {int sin_len; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_5__ {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
union sctp_sockstore {int /*<<< orphan*/  sa; TYPE_3__ sin; TYPE_1__ sin6; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  primary_destination; scalar_t__ asconf_supported; int /*<<< orphan*/  vrf_id; } ;
struct sctp_tcb {TYPE_4__ asoc; int /*<<< orphan*/  sctp_ep; int /*<<< orphan*/  rport; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ifa {int dummy; } ;
struct mbuf {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTP_ADDR_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF2 ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
#define  SCTP_IPV4_ADDRESS 129 
#define  SCTP_IPV6_ADDRESS 128 
 int /*<<< orphan*/  SCTP_PCB_FLAGS_DO_ASCONF ; 
 int /*<<< orphan*/  SCTP_PRINTF (char*,int,int) ; 
 scalar_t__ SCTP_SIZE32 (int) ; 
 scalar_t__ SCTP_STATE_OPEN ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_ASCONF ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union sctp_sockstore*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int sctp_asconf_queue_sa_delete (struct sctp_tcb*,int /*<<< orphan*/ *) ; 
 struct sctp_ifa* sctp_find_ifa_by_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_is_feature_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_m_getptr (struct mbuf*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_send_asconf (struct sctp_tcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sctp_process_initack_addresses(struct sctp_tcb *stcb, struct mbuf *m,
    unsigned int offset, unsigned int length)
{
	struct sctp_paramhdr tmp_param, *ph;
	uint16_t plen, ptype;
	struct sctp_ifa *sctp_ifa;
	union sctp_sockstore store;
#ifdef INET6
	struct sctp_ipv6addr_param addr6_store;
#endif
#ifdef INET
	struct sctp_ipv4addr_param addr4_store;
#endif

	SCTPDBG(SCTP_DEBUG_ASCONF2, "processing init-ack addresses\n");
	if (stcb == NULL)	/* Un-needed check for SA */
		return;

	/* convert to upper bound */
	length += offset;

	if ((offset + sizeof(struct sctp_paramhdr)) > length) {
		return;
	}
	/* go through the addresses in the init-ack */
	ph = (struct sctp_paramhdr *)
	    sctp_m_getptr(m, offset, sizeof(struct sctp_paramhdr),
	    (uint8_t *)&tmp_param);
	while (ph != NULL) {
		ptype = ntohs(ph->param_type);
		plen = ntohs(ph->param_length);
		switch (ptype) {
#ifdef INET6
		case SCTP_IPV6_ADDRESS:
			{
				struct sctp_ipv6addr_param *a6p;

				/* get the entire IPv6 address param */
				a6p = (struct sctp_ipv6addr_param *)
				    sctp_m_getptr(m, offset,
				    sizeof(struct sctp_ipv6addr_param),
				    (uint8_t *)&addr6_store);
				if (plen != sizeof(struct sctp_ipv6addr_param) ||
				    a6p == NULL) {
					return;
				}
				memset(&store, 0, sizeof(union sctp_sockstore));
				store.sin6.sin6_family = AF_INET6;
				store.sin6.sin6_len = sizeof(struct sockaddr_in6);
				store.sin6.sin6_port = stcb->rport;
				memcpy(&store.sin6.sin6_addr, a6p->addr, sizeof(struct in6_addr));
				break;
			}
#endif
#ifdef INET
		case SCTP_IPV4_ADDRESS:
			{
				struct sctp_ipv4addr_param *a4p;

				/* get the entire IPv4 address param */
				a4p = (struct sctp_ipv4addr_param *)sctp_m_getptr(m, offset,
				    sizeof(struct sctp_ipv4addr_param),
				    (uint8_t *)&addr4_store);
				if (plen != sizeof(struct sctp_ipv4addr_param) ||
				    a4p == NULL) {
					return;
				}
				memset(&store, 0, sizeof(union sctp_sockstore));
				store.sin.sin_family = AF_INET;
				store.sin.sin_len = sizeof(struct sockaddr_in);
				store.sin.sin_port = stcb->rport;
				store.sin.sin_addr.s_addr = a4p->addr;
				break;
			}
#endif
		default:
			goto next_addr;
		}

		/* see if this address really (still) exists */
		sctp_ifa = sctp_find_ifa_by_addr(&store.sa, stcb->asoc.vrf_id,
		    SCTP_ADDR_NOT_LOCKED);
		if (sctp_ifa == NULL) {
			/* address doesn't exist anymore */
			int status;

			/* are ASCONFs allowed ? */
			if ((sctp_is_feature_on(stcb->sctp_ep,
			    SCTP_PCB_FLAGS_DO_ASCONF)) &&
			    stcb->asoc.asconf_supported) {
				/* queue an ASCONF DEL_IP_ADDRESS */
				status = sctp_asconf_queue_sa_delete(stcb, &store.sa);
				/*
				 * if queued ok, and in correct state, send
				 * out the ASCONF.
				 */
				if (status == 0 &&
				    SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) {
#ifdef SCTP_TIMER_BASED_ASCONF
					sctp_timer_start(SCTP_TIMER_TYPE_ASCONF,
					    stcb->sctp_ep, stcb,
					    stcb->asoc.primary_destination);
#else
					sctp_send_asconf(stcb, NULL, SCTP_ADDR_NOT_LOCKED);
#endif
				}
			}
		}

next_addr:
		/*
		 * Sanity check:  Make sure the length isn't 0, otherwise
		 * we'll be stuck in this loop for a long time...
		 */
		if (SCTP_SIZE32(plen) == 0) {
			SCTP_PRINTF("process_initack_addrs: bad len (%d) type=%xh\n",
			    plen, ptype);
			return;
		}
		/* get next parameter */
		offset += SCTP_SIZE32(plen);
		if ((offset + sizeof(struct sctp_paramhdr)) > length)
			return;
		ph = (struct sctp_paramhdr *)sctp_m_getptr(m, offset,
		    sizeof(struct sctp_paramhdr), (uint8_t *)&tmp_param);
	}			/* while */
}