#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct TYPE_3__ {struct sctp_paramhdr* Asconf; } ;
struct sctp_nat_msg {int chunk_length; TYPE_2__* sctp_hdr; TYPE_1__ sctpchnk; } ;
struct libalias {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_tag; } ;

/* Variables and functions */
 int SCTP_SIZE32 (scalar_t__) ; 
 scalar_t__ SCTP_VTAG_PARAM ; 
 int /*<<< orphan*/  SN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG_EVENT ; 
 int SN_MIN_PARAM_SIZE ; 
 struct sctp_paramhdr* SN_SCTP_NEXTPARAM (struct sctp_paramhdr*) ; 
#define  SN_TO_GLOBAL 129 
#define  SN_TO_LOCAL 128 
 int SN_VTAG_PARAM_SIZE ; 
 int /*<<< orphan*/  logsctperror (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int sysctl_param_proc_limit ; 

__attribute__((used)) static int
GetAsconfVtags(struct libalias *la, struct sctp_nat_msg *sm, uint32_t *l_vtag, uint32_t *g_vtag, int direction)
{
	/* To be removed when information is in the sctp headers */
#define SCTP_VTAG_PARAM 0xC007
	struct sctp_vtag_param {
		struct sctp_paramhdr ph;/* type=SCTP_VTAG_PARAM */
		uint32_t local_vtag;
		uint32_t remote_vtag;
	}                    __attribute__((packed));

	struct sctp_vtag_param *vtag_param;
	struct sctp_paramhdr *param;
	int bytes_left;
	int param_size;
	int param_count;

	param_count = 1;
	param = sm->sctpchnk.Asconf;
	param_size = SCTP_SIZE32(ntohs(param->param_length));
	bytes_left = sm->chunk_length;
	/* step through Asconf parameters */
	while((bytes_left >= param_size) && (bytes_left >= SN_VTAG_PARAM_SIZE)) {
		if (ntohs(param->param_type) == SCTP_VTAG_PARAM) {
			vtag_param = (struct sctp_vtag_param *) param;
			switch (direction) {
				/* The Internet draft is a little ambigious as to order of these vtags.
				   We think it is this way around. If we are wrong, the order will need
				   to be changed. */
			case SN_TO_GLOBAL:
				*g_vtag = vtag_param->local_vtag;
				*l_vtag = vtag_param->remote_vtag;
				break;
			case SN_TO_LOCAL:
				*g_vtag = vtag_param->remote_vtag;
				*l_vtag = vtag_param->local_vtag;
				break;
			}
			return (1); /* found */
		}

		bytes_left -= param_size;
		if (bytes_left < SN_MIN_PARAM_SIZE) return (0);

		param = SN_SCTP_NEXTPARAM(param);
		param_size = SCTP_SIZE32(ntohs(param->param_length));
		if (++param_count > sysctl_param_proc_limit) {
			SN_LOG(SN_LOG_EVENT,
			    logsctperror("Parameter parse limit exceeded (GetAsconfVtags)",
				sm->sctp_hdr->v_tag, sysctl_param_proc_limit, direction));
			return (0); /* not found limit exceeded*/
		}
	}
	return (0); /* not found */
}