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
struct sctp_udpencaps {scalar_t__ sue_assoc_id; } ;
struct sctp_timeouts {scalar_t__ stimo_assoc_id; } ;
struct sctp_status {scalar_t__ sstat_assoc_id; } ;
struct sctp_sndinfo {scalar_t__ snd_assoc_id; } ;
struct sctp_setprim {scalar_t__ ssp_assoc_id; } ;
struct sctp_sack_info {scalar_t__ sack_assoc_id; } ;
struct sctp_rtoinfo {scalar_t__ srto_assoc_id; } ;
struct sctp_prstatus {scalar_t__ sprstat_assoc_id; } ;
struct sctp_paddrthlds {scalar_t__ spt_assoc_id; } ;
struct sctp_paddrparams {scalar_t__ spp_assoc_id; } ;
struct sctp_paddrinfo {scalar_t__ spinfo_assoc_id; } ;
struct sctp_event {scalar_t__ se_assoc_id; } ;
struct sctp_default_prinfo {scalar_t__ pr_assoc_id; } ;
struct sctp_authkeyid {scalar_t__ scact_assoc_id; } ;
struct sctp_authkey {scalar_t__ sca_assoc_id; } ;
struct sctp_authchunks {scalar_t__ gauth_assoc_id; } ;
struct sctp_assocparams {scalar_t__ sasoc_assoc_id; } ;
struct sctp_assoc_value {scalar_t__ assoc_id; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  scalar_t__ sctp_assoc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 scalar_t__ SCTP_ALL_ASSOC ; 
#define  SCTP_ASCONF_SUPPORTED 159 
#define  SCTP_ASSOCINFO 158 
#define  SCTP_AUTH_ACTIVE_KEY 157 
#define  SCTP_AUTH_KEY 156 
#define  SCTP_AUTH_SUPPORTED 155 
#define  SCTP_CONTEXT 154 
 scalar_t__ SCTP_CURRENT_ASSOC ; 
#define  SCTP_DEFAULT_PRINFO 153 
#define  SCTP_DEFAULT_SEND_PARAM 152 
#define  SCTP_DEFAULT_SNDINFO 151 
#define  SCTP_DELAYED_SACK 150 
#define  SCTP_ECN_SUPPORTED 149 
#define  SCTP_ENABLE_STREAM_RESET 148 
#define  SCTP_EVENT 147 
#define  SCTP_GET_PEER_ADDR_INFO 146 
#define  SCTP_LOCAL_AUTH_CHUNKS 145 
#define  SCTP_MAXSEG 144 
#define  SCTP_MAX_BURST 143 
#define  SCTP_MAX_CWND 142 
#define  SCTP_NRSACK_SUPPORTED 141 
#define  SCTP_PEER_ADDR_PARAMS 140 
#define  SCTP_PEER_ADDR_THLDS 139 
#define  SCTP_PEER_AUTH_CHUNKS 138 
#define  SCTP_PKTDROP_SUPPORTED 137 
#define  SCTP_PRIMARY_ADDR 136 
#define  SCTP_PR_ASSOC_STATUS 135 
#define  SCTP_PR_STREAM_STATUS 134 
#define  SCTP_PR_SUPPORTED 133 
#define  SCTP_RECONFIG_SUPPORTED 132 
#define  SCTP_REMOTE_UDP_ENCAPS_PORT 131 
#define  SCTP_RTOINFO 130 
#define  SCTP_STATUS 129 
#define  SCTP_TIMEOUTS 128 
 int /*<<< orphan*/  errno ; 
 int getsockopt (int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 

int
sctp_opt_info(int sd, sctp_assoc_t id, int opt, void *arg, socklen_t * size)
{
	if (arg == NULL) {
		errno = EINVAL;
		return (-1);
	}
	if ((id == SCTP_CURRENT_ASSOC) ||
	    (id == SCTP_ALL_ASSOC)) {
		errno = EINVAL;
		return (-1);
	}
	switch (opt) {
	case SCTP_RTOINFO:
		((struct sctp_rtoinfo *)arg)->srto_assoc_id = id;
		break;
	case SCTP_ASSOCINFO:
		((struct sctp_assocparams *)arg)->sasoc_assoc_id = id;
		break;
	case SCTP_DEFAULT_SEND_PARAM:
		((struct sctp_assocparams *)arg)->sasoc_assoc_id = id;
		break;
	case SCTP_PRIMARY_ADDR:
		((struct sctp_setprim *)arg)->ssp_assoc_id = id;
		break;
	case SCTP_PEER_ADDR_PARAMS:
		((struct sctp_paddrparams *)arg)->spp_assoc_id = id;
		break;
	case SCTP_MAXSEG:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_AUTH_KEY:
		((struct sctp_authkey *)arg)->sca_assoc_id = id;
		break;
	case SCTP_AUTH_ACTIVE_KEY:
		((struct sctp_authkeyid *)arg)->scact_assoc_id = id;
		break;
	case SCTP_DELAYED_SACK:
		((struct sctp_sack_info *)arg)->sack_assoc_id = id;
		break;
	case SCTP_CONTEXT:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_STATUS:
		((struct sctp_status *)arg)->sstat_assoc_id = id;
		break;
	case SCTP_GET_PEER_ADDR_INFO:
		((struct sctp_paddrinfo *)arg)->spinfo_assoc_id = id;
		break;
	case SCTP_PEER_AUTH_CHUNKS:
		((struct sctp_authchunks *)arg)->gauth_assoc_id = id;
		break;
	case SCTP_LOCAL_AUTH_CHUNKS:
		((struct sctp_authchunks *)arg)->gauth_assoc_id = id;
		break;
	case SCTP_TIMEOUTS:
		((struct sctp_timeouts *)arg)->stimo_assoc_id = id;
		break;
	case SCTP_EVENT:
		((struct sctp_event *)arg)->se_assoc_id = id;
		break;
	case SCTP_DEFAULT_SNDINFO:
		((struct sctp_sndinfo *)arg)->snd_assoc_id = id;
		break;
	case SCTP_DEFAULT_PRINFO:
		((struct sctp_default_prinfo *)arg)->pr_assoc_id = id;
		break;
	case SCTP_PEER_ADDR_THLDS:
		((struct sctp_paddrthlds *)arg)->spt_assoc_id = id;
		break;
	case SCTP_REMOTE_UDP_ENCAPS_PORT:
		((struct sctp_udpencaps *)arg)->sue_assoc_id = id;
		break;
	case SCTP_ECN_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_PR_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_AUTH_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_ASCONF_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_RECONFIG_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_NRSACK_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_PKTDROP_SUPPORTED:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_MAX_BURST:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_ENABLE_STREAM_RESET:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	case SCTP_PR_STREAM_STATUS:
		((struct sctp_prstatus *)arg)->sprstat_assoc_id = id;
		break;
	case SCTP_PR_ASSOC_STATUS:
		((struct sctp_prstatus *)arg)->sprstat_assoc_id = id;
		break;
	case SCTP_MAX_CWND:
		((struct sctp_assoc_value *)arg)->assoc_id = id;
		break;
	default:
		break;
	}
	return (getsockopt(sd, IPPROTO_SCTP, opt, arg, size));
}