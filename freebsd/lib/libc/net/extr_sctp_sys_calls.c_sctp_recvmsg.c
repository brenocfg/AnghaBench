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
struct sockaddr {int dummy; } ;
struct sctp_sndrcvinfo {scalar_t__ sinfo_assoc_id; } ;
struct sctp_extrcvinfo {int dummy; } ;
struct msghdr {int msg_iovlen; char* msg_control; int msg_controllen; int msg_flags; struct iovec* msg_iov; scalar_t__ msg_namelen; scalar_t__ msg_name; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  int ssize_t ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  cmsgbuf ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IPPROTO_SCTP ; 
 int SCTP_CONTROL_VEC_SIZE_RCV ; 
 scalar_t__ SCTP_EXTRCV ; 
 scalar_t__ SCTP_SNDRCV ; 
 int /*<<< orphan*/  SYS_sctp_generic_recvmsg ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (struct sctp_sndrcvinfo*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int,struct msghdr*,int) ; 
 int syscall (int /*<<< orphan*/ ,int,struct iovec*,int,struct sockaddr*,scalar_t__*,struct sctp_sndrcvinfo*,int*) ; 

ssize_t
sctp_recvmsg(int s,
    void *dbuf,
    size_t len,
    struct sockaddr *from,
    socklen_t * fromlen,
    struct sctp_sndrcvinfo *sinfo,
    int *msg_flags)
{
#ifdef SYS_sctp_generic_recvmsg
	struct iovec iov;

	iov.iov_base = dbuf;
	iov.iov_len = len;
	return (syscall(SYS_sctp_generic_recvmsg, s,
	    &iov, 1, from, fromlen, sinfo, msg_flags));
#else
	ssize_t sz;
	struct msghdr msg;
	struct iovec iov;
	char cmsgbuf[SCTP_CONTROL_VEC_SIZE_RCV];
	struct cmsghdr *cmsg;

	if (msg_flags == NULL) {
		errno = EINVAL;
		return (-1);
	}
	iov.iov_base = dbuf;
	iov.iov_len = len;
	msg.msg_name = (caddr_t)from;
	if (fromlen == NULL)
		msg.msg_namelen = 0;
	else
		msg.msg_namelen = *fromlen;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = cmsgbuf;
	msg.msg_controllen = sizeof(cmsgbuf);
	msg.msg_flags = 0;
	sz = recvmsg(s, &msg, *msg_flags);
	*msg_flags = msg.msg_flags;
	if (sz <= 0) {
		return (sz);
	}
	if (sinfo) {
		sinfo->sinfo_assoc_id = 0;
	}
	if ((msg.msg_controllen > 0) && (sinfo != NULL)) {
		/*
		 * parse through and see if we find the sctp_sndrcvinfo (if
		 * the user wants it).
		 */
		for (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
			if (cmsg->cmsg_level != IPPROTO_SCTP) {
				continue;
			}
			if (cmsg->cmsg_type == SCTP_SNDRCV) {
				memcpy(sinfo, CMSG_DATA(cmsg), sizeof(struct sctp_sndrcvinfo));
				break;
			}
			if (cmsg->cmsg_type == SCTP_EXTRCV) {
				/*
				 * Let's hope that the user provided enough
				 * enough memory. At least he asked for more
				 * information.
				 */
				memcpy(sinfo, CMSG_DATA(cmsg), sizeof(struct sctp_extrcvinfo));
				break;
			}
		}
	}
	return (sz);
#endif
}