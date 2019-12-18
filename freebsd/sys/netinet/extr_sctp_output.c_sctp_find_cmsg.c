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
struct sctp_sndrcvinfo {int sinfo_keynumber_valid; int /*<<< orphan*/  sinfo_keynumber; int /*<<< orphan*/  sinfo_flags; int /*<<< orphan*/  sinfo_timetolive; int /*<<< orphan*/  sinfo_assoc_id; int /*<<< orphan*/  sinfo_context; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_stream; } ;
struct sctp_sndinfo {int /*<<< orphan*/  snd_assoc_id; int /*<<< orphan*/  snd_context; int /*<<< orphan*/  snd_ppid; int /*<<< orphan*/  snd_flags; int /*<<< orphan*/  snd_sid; } ;
struct sctp_prinfo {int /*<<< orphan*/  pr_policy; int /*<<< orphan*/  pr_value; } ;
struct sctp_authinfo {int /*<<< orphan*/  auth_keynumber; } ;
struct mbuf {int dummy; } ;
struct cmsghdr {int cmsg_len; scalar_t__ cmsg_level; int cmsg_type; } ;
typedef  int /*<<< orphan*/  cmh ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ CMSG_ALIGN (int) ; 
 size_t INT_MAX ; 
 scalar_t__ IPPROTO_SCTP ; 
#define  SCTP_AUTHINFO 130 
 int SCTP_BUF_LEN (struct mbuf*) ; 
#define  SCTP_PRINFO 129 
 int /*<<< orphan*/  SCTP_PR_SCTP_NONE ; 
#define  SCTP_SNDINFO 128 
 int SCTP_SNDRCV ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sctp_sndrcvinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sctp_find_cmsg(int c_type, void *data, struct mbuf *control, size_t cpsize)
{
	struct cmsghdr cmh;
	struct sctp_sndinfo sndinfo;
	struct sctp_prinfo prinfo;
	struct sctp_authinfo authinfo;
	int tot_len, rem_len, cmsg_data_len, cmsg_data_off, off;
	int found;

	/*
	 * Independent of how many mbufs, find the c_type inside the control
	 * structure and copy out the data.
	 */
	found = 0;
	tot_len = SCTP_BUF_LEN(control);
	for (off = 0; off < tot_len; off += CMSG_ALIGN(cmh.cmsg_len)) {
		rem_len = tot_len - off;
		if (rem_len < (int)CMSG_ALIGN(sizeof(cmh))) {
			/* There is not enough room for one more. */
			return (found);
		}
		m_copydata(control, off, sizeof(cmh), (caddr_t)&cmh);
		if (cmh.cmsg_len < CMSG_ALIGN(sizeof(cmh))) {
			/* We dont't have a complete CMSG header. */
			return (found);
		}
		if ((cmh.cmsg_len > INT_MAX) || ((int)cmh.cmsg_len > rem_len)) {
			/* We don't have the complete CMSG. */
			return (found);
		}
		cmsg_data_len = (int)cmh.cmsg_len - CMSG_ALIGN(sizeof(cmh));
		cmsg_data_off = off + CMSG_ALIGN(sizeof(cmh));
		if ((cmh.cmsg_level == IPPROTO_SCTP) &&
		    ((c_type == cmh.cmsg_type) ||
		    ((c_type == SCTP_SNDRCV) &&
		    ((cmh.cmsg_type == SCTP_SNDINFO) ||
		    (cmh.cmsg_type == SCTP_PRINFO) ||
		    (cmh.cmsg_type == SCTP_AUTHINFO))))) {
			if (c_type == cmh.cmsg_type) {
				if (cpsize > INT_MAX) {
					return (found);
				}
				if (cmsg_data_len < (int)cpsize) {
					return (found);
				}
				/* It is exactly what we want. Copy it out. */
				m_copydata(control, cmsg_data_off, (int)cpsize, (caddr_t)data);
				return (1);
			} else {
				struct sctp_sndrcvinfo *sndrcvinfo;

				sndrcvinfo = (struct sctp_sndrcvinfo *)data;
				if (found == 0) {
					if (cpsize < sizeof(struct sctp_sndrcvinfo)) {
						return (found);
					}
					memset(sndrcvinfo, 0, sizeof(struct sctp_sndrcvinfo));
				}
				switch (cmh.cmsg_type) {
				case SCTP_SNDINFO:
					if (cmsg_data_len < (int)sizeof(struct sctp_sndinfo)) {
						return (found);
					}
					m_copydata(control, cmsg_data_off, sizeof(struct sctp_sndinfo), (caddr_t)&sndinfo);
					sndrcvinfo->sinfo_stream = sndinfo.snd_sid;
					sndrcvinfo->sinfo_flags = sndinfo.snd_flags;
					sndrcvinfo->sinfo_ppid = sndinfo.snd_ppid;
					sndrcvinfo->sinfo_context = sndinfo.snd_context;
					sndrcvinfo->sinfo_assoc_id = sndinfo.snd_assoc_id;
					break;
				case SCTP_PRINFO:
					if (cmsg_data_len < (int)sizeof(struct sctp_prinfo)) {
						return (found);
					}
					m_copydata(control, cmsg_data_off, sizeof(struct sctp_prinfo), (caddr_t)&prinfo);
					if (prinfo.pr_policy != SCTP_PR_SCTP_NONE) {
						sndrcvinfo->sinfo_timetolive = prinfo.pr_value;
					} else {
						sndrcvinfo->sinfo_timetolive = 0;
					}
					sndrcvinfo->sinfo_flags |= prinfo.pr_policy;
					break;
				case SCTP_AUTHINFO:
					if (cmsg_data_len < (int)sizeof(struct sctp_authinfo)) {
						return (found);
					}
					m_copydata(control, cmsg_data_off, sizeof(struct sctp_authinfo), (caddr_t)&authinfo);
					sndrcvinfo->sinfo_keynumber_valid = 1;
					sndrcvinfo->sinfo_keynumber = authinfo.auth_keynumber;
					break;
				default:
					return (found);
				}
				found = 1;
			}
		}
	}
	return (found);
}