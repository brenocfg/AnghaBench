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
struct sctphdr {scalar_t__ src_port; scalar_t__ dest_port; int /*<<< orphan*/  v_tag; } ;
struct sctp_shutdown_ack_chunk {int dummy; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_type; } ;
struct TYPE_2__ {struct sctp_paramhdr* Asconf; struct sctp_init_ack* InitAck; struct sctp_init* Init; } ;
struct sctp_nat_msg {int chunk_length; TYPE_1__ sctpchnk; int /*<<< orphan*/  msg; struct sctphdr* sctp_hdr; struct ip* ip_hdr; } ;
struct sctp_nat_assoc {void* TableRegister; int /*<<< orphan*/  Gaddr; void* state; } ;
struct sctp_ipv6addr_param {int dummy; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_init_chunk {int dummy; } ;
struct sctp_init_ack_chunk {int dummy; } ;
struct sctp_init_ack {int dummy; } ;
struct sctp_init {int dummy; } ;
struct sctp_chunkhdr {int chunk_flags; int chunk_type; int /*<<< orphan*/  chunk_length; } ;
struct sctp_asconf_chunk {int dummy; } ;
struct sctp_asconf_ack_chunk {int dummy; } ;
struct libalias {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_dst; struct in_addr ip_src; int /*<<< orphan*/  ip_len; } ;

/* Variables and functions */
 struct sctp_nat_assoc* FindSctpGlobal (struct libalias*,struct in_addr,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*) ; 
 struct sctp_nat_assoc* FindSctpGlobalT (struct libalias*,struct in_addr,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct sctp_nat_assoc* FindSctpLocal (struct libalias*,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct sctp_nat_assoc* FindSctpLocalT (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ IS_SCTP_CONTROL (struct sctp_chunkhdr*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
#define  SCTP_ABORT_ASSOCIATION 134 
#define  SCTP_ASCONF 133 
#define  SCTP_ASCONF_ACK 132 
 int SCTP_HAD_NO_TCB ; 
#define  SCTP_INITIATION 131 
#define  SCTP_INITIATION_ACK 130 
 int /*<<< orphan*/  SCTP_IPV4_ADDRESS ; 
#define  SCTP_SHUTDOWN_ACK 129 
#define  SCTP_SHUTDOWN_COMPLETE 128 
 int SCTP_SIZE32 (int /*<<< orphan*/ ) ; 
 void* SN_ID ; 
 int SN_MIN_CHUNK_SIZE ; 
 void* SN_NULL_TBL ; 
 int SN_PARSE_ERROR_AS_MALLOC ; 
 int SN_PARSE_ERROR_CHHL ; 
 int SN_PARSE_ERROR_IPSHL ; 
 int SN_PARSE_ERROR_LOOKUP ; 
 int SN_PARSE_ERROR_LOOKUP_ABORT ; 
 int SN_PARSE_ERROR_PARTIALLOOKUP ; 
 int SN_PARSE_ERROR_PORT ; 
 int SN_PARSE_ERROR_VTAG ; 
 int SN_PARSE_OK ; 
 int /*<<< orphan*/  SN_SCTP_ABORT ; 
 int /*<<< orphan*/  SN_SCTP_ASCONF ; 
 int /*<<< orphan*/  SN_SCTP_ASCONFACK ; 
 struct sctp_chunkhdr* SN_SCTP_FIRSTCHUNK (struct sctphdr*) ; 
 int /*<<< orphan*/  SN_SCTP_INIT ; 
 int /*<<< orphan*/  SN_SCTP_INITACK ; 
 struct sctp_chunkhdr* SN_SCTP_NEXTCHUNK (struct sctp_chunkhdr*) ; 
 int /*<<< orphan*/  SN_SCTP_OTHER ; 
 int /*<<< orphan*/  SN_SCTP_SHUTACK ; 
 int /*<<< orphan*/  SN_SCTP_SHUTCOMP ; 
 int SN_TO_LOCAL ; 
 scalar_t__ ip_next (struct ip*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sn_malloc (int) ; 
 int sysctl_chunk_proc_limit ; 
 int sysctl_initialising_chunk_proc_limit ; 

__attribute__((used)) static int
sctp_PktParser(struct libalias *la, int direction, struct ip *pip,
    struct sctp_nat_msg *sm, struct sctp_nat_assoc **passoc)
//sctp_PktParser(int direction, struct mbuf *ipak, int ip_hdr_len,struct sctp_nat_msg *sm, struct sctp_nat_assoc *assoc)
{
	struct sctphdr *sctp_hdr;
	struct sctp_chunkhdr *chunk_hdr;
	struct sctp_paramhdr *param_hdr;
	struct in_addr ipv4addr;
	int bytes_left; /* bytes left in ip packet */
	int chunk_length;
	int chunk_count;
	int partial_match = 0;
	//  mbuf *mp;
	//  int mlen;

	//  mlen = SCTP_HEADER_LEN(i_pak);
	//  mp = SCTP_HEADER_TO_CHAIN(i_pak); /* does nothing in bsd since header and chain not separate */

	/*
	 * Note, that if the VTag is zero, it must be an INIT
	 * Also, I am only interested in the content of INIT and ADDIP chunks
	 */

	// no mbuf stuff from Paolo yet so ...
	sm->ip_hdr = pip;
	/* remove ip header length from the bytes_left */
	bytes_left = ntohs(pip->ip_len) - (pip->ip_hl << 2);

	/* Check SCTP header length and move to first chunk */
	if (bytes_left < sizeof(struct sctphdr)) {
		sm->sctp_hdr = NULL;
		return (SN_PARSE_ERROR_IPSHL); /* packet not long enough*/
	}

	sm->sctp_hdr = sctp_hdr = (struct sctphdr *) ip_next(pip);
	bytes_left -= sizeof(struct sctphdr);

	/* Check for valid ports (zero valued ports would find partially initialised associations */
	if (sctp_hdr->src_port == 0 || sctp_hdr->dest_port == 0)
		return (SN_PARSE_ERROR_PORT);

	/* Check length of first chunk */
	if (bytes_left < SN_MIN_CHUNK_SIZE) /* malformed chunk - could cause endless loop*/
		return (SN_PARSE_ERROR_CHHL); /* packet not long enough for this chunk */

	/* First chunk */
	chunk_hdr = SN_SCTP_FIRSTCHUNK(sctp_hdr);

	chunk_length = SCTP_SIZE32(ntohs(chunk_hdr->chunk_length));
	if ((chunk_length < SN_MIN_CHUNK_SIZE) || (chunk_length > bytes_left)) /* malformed chunk - could cause endless loop*/
		return (SN_PARSE_ERROR_CHHL);

	if ((chunk_hdr->chunk_flags & SCTP_HAD_NO_TCB) &&
	    ((chunk_hdr->chunk_type == SCTP_ABORT_ASSOCIATION) ||
		(chunk_hdr->chunk_type == SCTP_SHUTDOWN_COMPLETE))) {
		/* T-Bit set */
		if (direction == SN_TO_LOCAL)
			*passoc = FindSctpGlobalT(la,  pip->ip_src, sctp_hdr->v_tag, sctp_hdr->dest_port, sctp_hdr->src_port);
		else
			*passoc = FindSctpLocalT(la, pip->ip_dst, sctp_hdr->v_tag, sctp_hdr->dest_port, sctp_hdr->src_port);
	} else {
		/* Proper v_tag settings */
		if (direction == SN_TO_LOCAL)
			*passoc = FindSctpGlobal(la, pip->ip_src, sctp_hdr->v_tag, sctp_hdr->src_port, sctp_hdr->dest_port, &partial_match);
		else
			*passoc = FindSctpLocal(la, pip->ip_src,  pip->ip_dst, sctp_hdr->v_tag, sctp_hdr->src_port, sctp_hdr->dest_port);
	}

	chunk_count = 1;
	/* Real packet parsing occurs below */
	sm->msg = SN_SCTP_OTHER;/* Initialise to largest value*/
	sm->chunk_length = 0; /* only care about length for key chunks */
	while (IS_SCTP_CONTROL(chunk_hdr)) {
		switch (chunk_hdr->chunk_type) {
		case SCTP_INITIATION:
			if (chunk_length < sizeof(struct sctp_init_chunk)) /* malformed chunk*/
				return (SN_PARSE_ERROR_CHHL);
			sm->msg = SN_SCTP_INIT;
			sm->sctpchnk.Init = (struct sctp_init *) ((char *) chunk_hdr + sizeof(struct sctp_chunkhdr));
			sm->chunk_length = chunk_length;
			/* if no existing association, create a new one */
			if (*passoc == NULL) {
				if (sctp_hdr->v_tag == 0) { //Init requires vtag=0
					*passoc = (struct sctp_nat_assoc *) sn_malloc(sizeof(struct sctp_nat_assoc));
					if (*passoc == NULL) {/* out of resources */
						return (SN_PARSE_ERROR_AS_MALLOC);
					}
					/* Initialize association - sn_malloc initializes memory to zeros */
					(*passoc)->state = SN_ID;
					LIST_INIT(&((*passoc)->Gaddr)); /* always initialise to avoid memory problems */
					(*passoc)->TableRegister = SN_NULL_TBL;
					return (SN_PARSE_OK);
				}
				return (SN_PARSE_ERROR_VTAG);
			}
			return (SN_PARSE_ERROR_LOOKUP);
		case SCTP_INITIATION_ACK:
			if (chunk_length < sizeof(struct sctp_init_ack_chunk)) /* malformed chunk*/
				return (SN_PARSE_ERROR_CHHL);
			sm->msg = SN_SCTP_INITACK;
			sm->sctpchnk.InitAck = (struct sctp_init_ack *) ((char *) chunk_hdr + sizeof(struct sctp_chunkhdr));
			sm->chunk_length = chunk_length;
			return ((*passoc == NULL) ? (SN_PARSE_ERROR_LOOKUP) : (SN_PARSE_OK));
		case SCTP_ABORT_ASSOCIATION: /* access only minimum sized chunk */
			sm->msg = SN_SCTP_ABORT;
			sm->chunk_length = chunk_length;
			return ((*passoc == NULL) ? (SN_PARSE_ERROR_LOOKUP_ABORT) : (SN_PARSE_OK));
		case SCTP_SHUTDOWN_ACK:
			if (chunk_length < sizeof(struct sctp_shutdown_ack_chunk)) /* malformed chunk*/
				return (SN_PARSE_ERROR_CHHL);
			if (sm->msg > SN_SCTP_SHUTACK) {
				sm->msg = SN_SCTP_SHUTACK;
				sm->chunk_length = chunk_length;
			}
			break;
		case SCTP_SHUTDOWN_COMPLETE:  /* minimum sized chunk */
			if (sm->msg > SN_SCTP_SHUTCOMP) {
				sm->msg = SN_SCTP_SHUTCOMP;
				sm->chunk_length = chunk_length;
			}
			return ((*passoc == NULL) ? (SN_PARSE_ERROR_LOOKUP) : (SN_PARSE_OK));
		case SCTP_ASCONF:
			if (sm->msg > SN_SCTP_ASCONF) {
				if (chunk_length < (sizeof(struct  sctp_asconf_chunk) + sizeof(struct  sctp_ipv4addr_param))) /* malformed chunk*/
					return (SN_PARSE_ERROR_CHHL);
				//leave parameter searching to later, if required
				param_hdr = (struct sctp_paramhdr *) ((char *) chunk_hdr + sizeof(struct sctp_asconf_chunk)); /*compulsory IP parameter*/
				if (ntohs(param_hdr->param_type) == SCTP_IPV4_ADDRESS) {
					if ((*passoc == NULL) && (direction == SN_TO_LOCAL)) { /* AddIP with no association */
						/* try look up with the ASCONF packet's alternative address */
						ipv4addr.s_addr = ((struct sctp_ipv4addr_param *) param_hdr)->addr;
						*passoc = FindSctpGlobal(la, ipv4addr, sctp_hdr->v_tag, sctp_hdr->src_port, sctp_hdr->dest_port, &partial_match);
					}
					param_hdr = (struct sctp_paramhdr *)
						((char *) param_hdr + sizeof(struct sctp_ipv4addr_param)); /*asconf's compulsory address parameter */
					sm->chunk_length = chunk_length - sizeof(struct  sctp_asconf_chunk) - sizeof(struct  sctp_ipv4addr_param); /* rest of chunk */
				} else {
					if (chunk_length < (sizeof(struct  sctp_asconf_chunk) + sizeof(struct  sctp_ipv6addr_param))) /* malformed chunk*/
						return (SN_PARSE_ERROR_CHHL);
					param_hdr = (struct sctp_paramhdr *)
						((char *) param_hdr + sizeof(struct sctp_ipv6addr_param)); /*asconf's compulsory address parameter */
					sm->chunk_length = chunk_length - sizeof(struct  sctp_asconf_chunk) - sizeof(struct  sctp_ipv6addr_param); /* rest of chunk */
				}
				sm->msg = SN_SCTP_ASCONF;
				sm->sctpchnk.Asconf = param_hdr;

				if (*passoc == NULL) { /* AddIP with no association */
					*passoc = (struct sctp_nat_assoc *) sn_malloc(sizeof(struct sctp_nat_assoc));
					if (*passoc == NULL) {/* out of resources */
						return (SN_PARSE_ERROR_AS_MALLOC);
					}
					/* Initialize association  - sn_malloc initializes memory to zeros */
					(*passoc)->state = SN_ID;
					LIST_INIT(&((*passoc)->Gaddr)); /* always initialise to avoid memory problems */
					(*passoc)->TableRegister = SN_NULL_TBL;
					return (SN_PARSE_OK);
				}
			}
			break;
		case SCTP_ASCONF_ACK:
			if (sm->msg > SN_SCTP_ASCONFACK) {
				if (chunk_length < sizeof(struct  sctp_asconf_ack_chunk)) /* malformed chunk*/
					return (SN_PARSE_ERROR_CHHL);
				//leave parameter searching to later, if required
				param_hdr = (struct sctp_paramhdr *) ((char *) chunk_hdr
				    + sizeof(struct sctp_asconf_ack_chunk));
				sm->msg = SN_SCTP_ASCONFACK;
				sm->sctpchnk.Asconf = param_hdr;
				sm->chunk_length = chunk_length - sizeof(struct sctp_asconf_ack_chunk);
			}
			break;
		default:
			break; /* do nothing*/
		}

		/* if no association is found exit - we need to find an Init or AddIP within sysctl_initialising_chunk_proc_limit */
		if ((*passoc == NULL) && (chunk_count >= sysctl_initialising_chunk_proc_limit))
			return (SN_PARSE_ERROR_LOOKUP);

		/* finished with this chunk, on to the next chunk*/
		bytes_left-= chunk_length;

		/* Is this the end of the packet ? */
		if (bytes_left == 0)
			return (*passoc == NULL) ? (SN_PARSE_ERROR_LOOKUP) : (SN_PARSE_OK);

		/* Are there enough bytes in packet to at least retrieve length of next chunk ? */
		if (bytes_left < SN_MIN_CHUNK_SIZE)
			return (SN_PARSE_ERROR_CHHL);

		chunk_hdr = SN_SCTP_NEXTCHUNK(chunk_hdr);

		/* Is the chunk long enough to not cause endless look and are there enough bytes in packet to read the chunk ? */
		chunk_length = SCTP_SIZE32(ntohs(chunk_hdr->chunk_length));
		if ((chunk_length < SN_MIN_CHUNK_SIZE) || (chunk_length > bytes_left))
			return (SN_PARSE_ERROR_CHHL);
		if (++chunk_count > sysctl_chunk_proc_limit)
			return (SN_PARSE_OK); /* limit for processing chunks, take what we get */
	}

	if (*passoc == NULL)
		return (partial_match) ? (SN_PARSE_ERROR_PARTIALLOOKUP) : (SN_PARSE_ERROR_LOOKUP);
	else
		return (SN_PARSE_OK);
}