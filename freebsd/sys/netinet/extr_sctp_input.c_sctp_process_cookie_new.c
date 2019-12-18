#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_14__ {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_family; TYPE_5__ sin_addr; int /*<<< orphan*/  sin_family; } ;
union sctp_sockstore {int /*<<< orphan*/  sa; TYPE_7__ sin6; TYPE_7__ sin; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sctphdr {int dummy; } ;
struct TYPE_10__ {scalar_t__ ipv4_addr_legal; scalar_t__ ipv6_addr_legal; int /*<<< orphan*/  loopback_scope; int /*<<< orphan*/  local_scope; int /*<<< orphan*/  site_scope; int /*<<< orphan*/  ipv4_local_scope; } ;
struct sctp_association {int authenticated; int state; int /*<<< orphan*/  time_entered; scalar_t__ sctp_autoclose_ticks; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * primary_destination; void* last_acked_seq; void* advanced_peer_ack_point; void* init_seq_number; void* str_reset_seq_in; void* asconf_seq_in; void* asconf_seq_out; void* asconf_seq_out_acked; void* str_reset_seq_out; void* sending_seq; int /*<<< orphan*/  pre_open_streams; void* my_rwnd; void* my_vtag; TYPE_3__ scope; } ;
struct sctp_tcb {struct sctp_association asoc; struct sctp_inpcb* sctp_ep; int /*<<< orphan*/  sctp_socket; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sctp_state_cookie {scalar_t__ ipv4_addr_legal; scalar_t__ ipv6_addr_legal; int laddr_type; int /*<<< orphan*/  loopback_scope; int /*<<< orphan*/  ipv4_scope; int /*<<< orphan*/  site_scope; int /*<<< orphan*/  local_scope; TYPE_6__ time_entered; int /*<<< orphan*/ * laddress; int /*<<< orphan*/  scope_id; } ;
struct sctp_nets {int hb_responded; } ;
struct sctp_inpcb {int sctp_flags; } ;
struct TYPE_8__ {scalar_t__ chunk_type; int /*<<< orphan*/  chunk_length; } ;
struct sctp_init_chunk {TYPE_1__ ch; } ;
struct TYPE_11__ {int /*<<< orphan*/  initial_tsn; int /*<<< orphan*/  num_outbound_streams; int /*<<< orphan*/  a_rwnd; int /*<<< orphan*/  initiate_tag; } ;
struct TYPE_9__ {scalar_t__ chunk_type; } ;
struct sctp_init_ack_chunk {TYPE_4__ init; TYPE_2__ ch; } ;
struct sctp_cookie_echo_chunk {int dummy; } ;
struct sctp_auth_chunk {int dummy; } ;
struct mbuf {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTP_CAUSE_OUT_OF_RESC ; 
 int /*<<< orphan*/  SCTP_DEBUG_AUTH1 ; 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT1 ; 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
 int /*<<< orphan*/  SCTP_DONT_INITIALIZE_AUTH_PARAMS ; 
 scalar_t__ SCTP_FROM_SCTP_INPUT ; 
 int /*<<< orphan*/  SCTP_GETTIME_TIMEVAL (int /*<<< orphan*/ *) ; 
 scalar_t__ SCTP_INITIATION ; 
 scalar_t__ SCTP_INITIATION_ACK ; 
 struct socket* SCTP_INP_SO (struct sctp_inpcb*) ; 
#define  SCTP_IPV4_ADDRESS 129 
#define  SCTP_IPV6_ADDRESS 128 
 scalar_t__ SCTP_IS_LISTENING (struct sctp_inpcb*) ; 
 scalar_t__ SCTP_LOC_18 ; 
 scalar_t__ SCTP_LOC_19 ; 
 scalar_t__ SCTP_LOC_20 ; 
 scalar_t__ SCTP_LOC_21 ; 
 scalar_t__ SCTP_LOC_22 ; 
 int /*<<< orphan*/  SCTP_NORMAL_PROC ; 
 int SCTP_NOTIFY_ASSOC_UP ; 
 int SCTP_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SCTP_PCB_FLAGS_AUTOCLOSE ; 
 int SCTP_PCB_FLAGS_CONNECTED ; 
 int SCTP_PCB_FLAGS_IN_TCPPOOL ; 
 int SCTP_PCB_FLAGS_TCPTYPE ; 
 int /*<<< orphan*/  SCTP_RTT_FROM_NON_DATA ; 
 int /*<<< orphan*/  SCTP_SET_STATE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int SCTP_SIZE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_SOCKET_LOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_UNLOCK (struct socket*,int) ; 
 int SCTP_STATE_CLOSED_SOCKET ; 
 int /*<<< orphan*/  SCTP_STATE_OPEN ; 
 int SCTP_STATE_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  SCTP_STAT_INCR_COUNTER32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STAT_INCR_GAUGE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_AUTOCLOSE ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWNGUARD ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_abort_association (struct sctp_inpcb*,struct sctp_tcb*,struct mbuf*,int,struct sockaddr*,struct sockaddr*,struct sctphdr*,struct mbuf*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct sctp_tcb* sctp_aloc_assoc (struct sctp_inpcb*,struct sockaddr*,int*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_get_cookie_params (struct sctp_tcb*,struct mbuf*,int,int) ; 
 int /*<<< orphan*/  sctp_calculate_rto (struct sctp_tcb*,struct sctp_association*,struct sctp_nets*,struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_check_address_list (struct sctp_tcb*,struct mbuf*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_nets* sctp_findnet (struct sctp_tcb*,struct sockaddr*) ; 
 int /*<<< orphan*/  sctp_free_assoc (struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mbuf* sctp_generate_cause (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sctp_handle_auth (struct sctp_tcb*,struct sctp_auth_chunk*,struct mbuf*,int) ; 
 scalar_t__ sctp_is_feature_on (struct sctp_inpcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_load_addresses_from_init (struct sctp_tcb*,struct mbuf*,int,int,struct sockaddr*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_m_getptr (struct mbuf*,int,int,int /*<<< orphan*/ *) ; 
 int sctp_process_init (struct sctp_init_chunk*,struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_send_cookie_ack (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_stop_all_cookie_timers (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctps_currestab ; 
 int /*<<< orphan*/  sctps_passiveestab ; 
 int /*<<< orphan*/  soisconnected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_tcb *
sctp_process_cookie_new(struct mbuf *m, int iphlen, int offset,
    struct sockaddr *src, struct sockaddr *dst,
    struct sctphdr *sh, struct sctp_state_cookie *cookie, int cookie_len,
    struct sctp_inpcb *inp, struct sctp_nets **netp,
    struct sockaddr *init_src, int *notification,
    int auth_skipped, uint32_t auth_offset, uint32_t auth_len,
    uint8_t mflowtype, uint32_t mflowid,
    uint32_t vrf_id, uint16_t port)
{
	struct sctp_tcb *stcb;
	struct sctp_init_chunk *init_cp, init_buf;
	struct sctp_init_ack_chunk *initack_cp, initack_buf;
	union sctp_sockstore store;
	struct sctp_association *asoc;
	int init_offset, initack_offset, initack_limit;
	int retval;
	int error = 0;
	uint8_t auth_chunk_buf[SCTP_PARAM_BUFFER_SIZE];
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	struct socket *so;

	so = SCTP_INP_SO(inp);
#endif

	/*
	 * find and validate the INIT chunk in the cookie (peer's info) the
	 * INIT should start after the cookie-echo header struct (chunk
	 * header, state cookie header struct)
	 */
	init_offset = offset + sizeof(struct sctp_cookie_echo_chunk);
	init_cp = (struct sctp_init_chunk *)
	    sctp_m_getptr(m, init_offset, sizeof(struct sctp_init_chunk),
	    (uint8_t *)&init_buf);
	if (init_cp == NULL) {
		/* could not pull a INIT chunk in cookie */
		SCTPDBG(SCTP_DEBUG_INPUT1,
		    "process_cookie_new: could not pull INIT chunk hdr\n");
		return (NULL);
	}
	if (init_cp->ch.chunk_type != SCTP_INITIATION) {
		SCTPDBG(SCTP_DEBUG_INPUT1, "HUH? process_cookie_new: could not find INIT chunk!\n");
		return (NULL);
	}
	initack_offset = init_offset + SCTP_SIZE32(ntohs(init_cp->ch.chunk_length));
	/*
	 * find and validate the INIT-ACK chunk in the cookie (my info) the
	 * INIT-ACK follows the INIT chunk
	 */
	initack_cp = (struct sctp_init_ack_chunk *)
	    sctp_m_getptr(m, initack_offset, sizeof(struct sctp_init_ack_chunk),
	    (uint8_t *)&initack_buf);
	if (initack_cp == NULL) {
		/* could not pull INIT-ACK chunk in cookie */
		SCTPDBG(SCTP_DEBUG_INPUT1, "process_cookie_new: could not pull INIT-ACK chunk hdr\n");
		return (NULL);
	}
	if (initack_cp->ch.chunk_type != SCTP_INITIATION_ACK) {
		return (NULL);
	}
	/*
	 * NOTE: We can't use the INIT_ACK's chk_length to determine the
	 * "initack_limit" value.  This is because the chk_length field
	 * includes the length of the cookie, but the cookie is omitted when
	 * the INIT and INIT_ACK are tacked onto the cookie...
	 */
	initack_limit = offset + cookie_len;

	/*
	 * now that we know the INIT/INIT-ACK are in place, create a new TCB
	 * and popluate
	 */

	/*
	 * Here we do a trick, we set in NULL for the proc/thread argument.
	 * We do this since in effect we only use the p argument when the
	 * socket is unbound and we must do an implicit bind. Since we are
	 * getting a cookie, we cannot be unbound.
	 */
	stcb = sctp_aloc_assoc(inp, init_src, &error,
	    ntohl(initack_cp->init.initiate_tag), vrf_id,
	    ntohs(initack_cp->init.num_outbound_streams),
	    port,
	    (struct thread *)NULL,
	    SCTP_DONT_INITIALIZE_AUTH_PARAMS);
	if (stcb == NULL) {
		struct mbuf *op_err;

		/* memory problem? */
		SCTPDBG(SCTP_DEBUG_INPUT1,
		    "process_cookie_new: no room for another TCB!\n");
		op_err = sctp_generate_cause(SCTP_CAUSE_OUT_OF_RESC, "");
		sctp_abort_association(inp, (struct sctp_tcb *)NULL, m, iphlen,
		    src, dst, sh, op_err,
		    mflowtype, mflowid,
		    vrf_id, port);
		return (NULL);
	}
	/* get the correct sctp_nets */
	if (netp)
		*netp = sctp_findnet(stcb, init_src);

	asoc = &stcb->asoc;
	/* get scope variables out of cookie */
	asoc->scope.ipv4_local_scope = cookie->ipv4_scope;
	asoc->scope.site_scope = cookie->site_scope;
	asoc->scope.local_scope = cookie->local_scope;
	asoc->scope.loopback_scope = cookie->loopback_scope;

	if ((asoc->scope.ipv4_addr_legal != cookie->ipv4_addr_legal) ||
	    (asoc->scope.ipv6_addr_legal != cookie->ipv6_addr_legal)) {
		struct mbuf *op_err;

		/*
		 * Houston we have a problem. The EP changed while the
		 * cookie was in flight. Only recourse is to abort the
		 * association.
		 */
		op_err = sctp_generate_cause(SCTP_CAUSE_OUT_OF_RESC, "");
		sctp_abort_association(inp, (struct sctp_tcb *)NULL, m, iphlen,
		    src, dst, sh, op_err,
		    mflowtype, mflowid,
		    vrf_id, port);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
		(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
		    SCTP_FROM_SCTP_INPUT + SCTP_LOC_18);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
		return (NULL);
	}
	/* process the INIT-ACK info (my info) */
	asoc->my_vtag = ntohl(initack_cp->init.initiate_tag);
	asoc->my_rwnd = ntohl(initack_cp->init.a_rwnd);
	asoc->pre_open_streams = ntohs(initack_cp->init.num_outbound_streams);
	asoc->init_seq_number = ntohl(initack_cp->init.initial_tsn);
	asoc->sending_seq = asoc->asconf_seq_out = asoc->str_reset_seq_out = asoc->init_seq_number;
	asoc->asconf_seq_out_acked = asoc->asconf_seq_out - 1;
	asoc->asconf_seq_in = asoc->last_acked_seq = asoc->init_seq_number - 1;
	asoc->str_reset_seq_in = asoc->init_seq_number;

	asoc->advanced_peer_ack_point = asoc->last_acked_seq;

	/* process the INIT info (peer's info) */
	if (netp)
		retval = sctp_process_init(init_cp, stcb);
	else
		retval = 0;
	if (retval < 0) {
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
		(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
		    SCTP_FROM_SCTP_INPUT + SCTP_LOC_19);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
		return (NULL);
	}
	/* load all addresses */
	if (sctp_load_addresses_from_init(stcb, m,
	    init_offset + sizeof(struct sctp_init_chunk), initack_offset,
	    src, dst, init_src, port)) {
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
		(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
		    SCTP_FROM_SCTP_INPUT + SCTP_LOC_20);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
		return (NULL);
	}
	/*
	 * verify any preceding AUTH chunk that was skipped
	 */
	/* pull the local authentication parameters from the cookie/init-ack */
	sctp_auth_get_cookie_params(stcb, m,
	    initack_offset + sizeof(struct sctp_init_ack_chunk),
	    initack_limit - (initack_offset + sizeof(struct sctp_init_ack_chunk)));
	if (auth_skipped) {
		struct sctp_auth_chunk *auth;

		auth = (struct sctp_auth_chunk *)
		    sctp_m_getptr(m, auth_offset, auth_len, auth_chunk_buf);
		if ((auth == NULL) || sctp_handle_auth(stcb, auth, m, auth_offset)) {
			/* auth HMAC failed, dump the assoc and packet */
			SCTPDBG(SCTP_DEBUG_AUTH1,
			    "COOKIE-ECHO: AUTH failed\n");
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
			atomic_add_int(&stcb->asoc.refcnt, 1);
			SCTP_TCB_UNLOCK(stcb);
			SCTP_SOCKET_LOCK(so, 1);
			SCTP_TCB_LOCK(stcb);
			atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
			(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
			    SCTP_FROM_SCTP_INPUT + SCTP_LOC_21);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
			SCTP_SOCKET_UNLOCK(so, 1);
#endif
			return (NULL);
		} else {
			/* remaining chunks checked... good to go */
			stcb->asoc.authenticated = 1;
		}
	}

	/*
	 * if we're doing ASCONFs, check to see if we have any new local
	 * addresses that need to get added to the peer (eg. addresses
	 * changed while cookie echo in flight).  This needs to be done
	 * after we go to the OPEN state to do the correct asconf
	 * processing. else, make sure we have the correct addresses in our
	 * lists
	 */

	/* warning, we re-use sin, sin6, sa_store here! */
	/* pull in local_address (our "from" address) */
	switch (cookie->laddr_type) {
#ifdef INET
	case SCTP_IPV4_ADDRESS:
		/* source addr is IPv4 */
		memset(&store.sin, 0, sizeof(struct sockaddr_in));
		store.sin.sin_family = AF_INET;
		store.sin.sin_len = sizeof(struct sockaddr_in);
		store.sin.sin_addr.s_addr = cookie->laddress[0];
		break;
#endif
#ifdef INET6
	case SCTP_IPV6_ADDRESS:
		/* source addr is IPv6 */
		memset(&store.sin6, 0, sizeof(struct sockaddr_in6));
		store.sin6.sin6_family = AF_INET6;
		store.sin6.sin6_len = sizeof(struct sockaddr_in6);
		store.sin6.sin6_scope_id = cookie->scope_id;
		memcpy(&store.sin6.sin6_addr, cookie->laddress, sizeof(struct in6_addr));
		break;
#endif
	default:
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
		(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
		    SCTP_FROM_SCTP_INPUT + SCTP_LOC_22);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
		return (NULL);
	}

	/* update current state */
	SCTPDBG(SCTP_DEBUG_INPUT2, "moving to OPEN state\n");
	SCTP_SET_STATE(stcb, SCTP_STATE_OPEN);
	if (asoc->state & SCTP_STATE_SHUTDOWN_PENDING) {
		sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWNGUARD,
		    stcb->sctp_ep, stcb, asoc->primary_destination);
	}
	sctp_stop_all_cookie_timers(stcb);
	SCTP_STAT_INCR_COUNTER32(sctps_passiveestab);
	SCTP_STAT_INCR_GAUGE32(sctps_currestab);

	/* set up to notify upper layer */
	*notification = SCTP_NOTIFY_ASSOC_UP;
	if (((stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_TCPTYPE) ||
	    (stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_IN_TCPPOOL)) &&
	    (!SCTP_IS_LISTENING(inp))) {
		/*
		 * This is an endpoint that called connect() how it got a
		 * cookie that is NEW is a bit of a mystery. It must be that
		 * the INIT was sent, but before it got there.. a complete
		 * INIT/INIT-ACK/COOKIE arrived. But of course then it
		 * should have went to the other code.. not here.. oh well..
		 * a bit of protection is worth having..
		 */
		stcb->sctp_ep->sctp_flags |= SCTP_PCB_FLAGS_CONNECTED;
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
		if (stcb->asoc.state & SCTP_STATE_CLOSED_SOCKET) {
			SCTP_SOCKET_UNLOCK(so, 1);
			return (NULL);
		}
#endif
		soisconnected(stcb->sctp_socket);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
	} else if ((stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_TCPTYPE) &&
	    (SCTP_IS_LISTENING(inp))) {
		/*
		 * We don't want to do anything with this one. Since it is
		 * the listening guy. The timer will get started for
		 * accepted connections in the caller.
		 */
		;
	}
	/* since we did not send a HB make sure we don't double things */
	if ((netp) && (*netp))
		(*netp)->hb_responded = 1;

	if (stcb->asoc.sctp_autoclose_ticks &&
	    sctp_is_feature_on(inp, SCTP_PCB_FLAGS_AUTOCLOSE)) {
		sctp_timer_start(SCTP_TIMER_TYPE_AUTOCLOSE, inp, stcb, NULL);
	}
	(void)SCTP_GETTIME_TIMEVAL(&stcb->asoc.time_entered);
	if ((netp != NULL) && (*netp != NULL)) {
		struct timeval old;

		/* calculate the RTT and set the encaps port */
		old.tv_sec = cookie->time_entered.tv_sec;
		old.tv_usec = cookie->time_entered.tv_usec;
		sctp_calculate_rto(stcb, asoc, *netp, &old, SCTP_RTT_FROM_NON_DATA);
	}
	/* respond with a COOKIE-ACK */
	sctp_send_cookie_ack(stcb);

	/*
	 * check the address lists for any ASCONFs that need to be sent
	 * AFTER the cookie-ack is sent
	 */
	sctp_check_address_list(stcb, m,
	    initack_offset + sizeof(struct sctp_init_ack_chunk),
	    initack_limit - (initack_offset + sizeof(struct sctp_init_ack_chunk)),
	    &store.sa, cookie->local_scope, cookie->site_scope,
	    cookie->ipv4_scope, cookie->loopback_scope);


	return (stcb);
}