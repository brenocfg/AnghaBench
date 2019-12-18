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
struct sctp_sndrcvinfo {int dummy; } ;
struct sctp_sndinfo {int dummy; } ;
struct sctp_rcvinfo {int dummy; } ;
struct sctp_prinfo {int dummy; } ;
struct sctp_nxtinfo {int dummy; } ;
struct sctp_initmsg {int dummy; } ;
struct sctp_extrcvinfo {int dummy; } ;
struct sctp_authinfo {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct cmsghdr {int cmsg_type; int /*<<< orphan*/  cmsg_len; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
#define  SCTP_AUTHINFO 137 
#define  SCTP_DSTADDRV4 136 
#define  SCTP_DSTADDRV6 135 
#define  SCTP_EXTRCV 134 
#define  SCTP_INIT 133 
#define  SCTP_NXTINFO 132 
#define  SCTP_PRINFO 131 
#define  SCTP_RCVINFO 130 
#define  SCTP_SNDINFO 129 
#define  SCTP_SNDRCV 128 
 int /*<<< orphan*/  print_gen_cmsg (int /*<<< orphan*/ *,struct cmsghdr*) ; 
 int /*<<< orphan*/  print_sctp_authinfo (int /*<<< orphan*/ *,struct sctp_authinfo*) ; 
 int /*<<< orphan*/  print_sctp_extrcvinfo (int /*<<< orphan*/ *,struct sctp_extrcvinfo*) ; 
 int /*<<< orphan*/  print_sctp_initmsg (int /*<<< orphan*/ *,struct sctp_initmsg*) ; 
 int /*<<< orphan*/  print_sctp_ipv4_addr (int /*<<< orphan*/ *,struct in_addr*) ; 
 int /*<<< orphan*/  print_sctp_ipv6_addr (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  print_sctp_nxtinfo (int /*<<< orphan*/ *,struct sctp_nxtinfo*) ; 
 int /*<<< orphan*/  print_sctp_prinfo (int /*<<< orphan*/ *,struct sctp_prinfo*) ; 
 int /*<<< orphan*/  print_sctp_rcvinfo (int /*<<< orphan*/ *,struct sctp_rcvinfo*) ; 
 int /*<<< orphan*/  print_sctp_sndinfo (int /*<<< orphan*/ *,struct sctp_sndinfo*) ; 
 int /*<<< orphan*/  print_sctp_sndrcvinfo (int /*<<< orphan*/ *,int,struct sctp_sndrcvinfo*) ; 

__attribute__((used)) static void
print_sctp_cmsg(FILE *fp, bool receive, struct cmsghdr *cmsghdr)
{
	void *data;
	socklen_t len;

	len = cmsghdr->cmsg_len;
	data = CMSG_DATA(cmsghdr);
	switch (cmsghdr->cmsg_type) {
	case SCTP_INIT:
		if (len == CMSG_LEN(sizeof(struct sctp_initmsg)))
			print_sctp_initmsg(fp, (struct sctp_initmsg *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_SNDRCV:
		if (len == CMSG_LEN(sizeof(struct sctp_sndrcvinfo)))
			print_sctp_sndrcvinfo(fp, receive,
			    (struct sctp_sndrcvinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
#if 0
	case SCTP_EXTRCV:
		if (len == CMSG_LEN(sizeof(struct sctp_extrcvinfo)))
			print_sctp_extrcvinfo(fp,
			    (struct sctp_extrcvinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
#endif
	case SCTP_SNDINFO:
		if (len == CMSG_LEN(sizeof(struct sctp_sndinfo)))
			print_sctp_sndinfo(fp, (struct sctp_sndinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_RCVINFO:
		if (len == CMSG_LEN(sizeof(struct sctp_rcvinfo)))
			print_sctp_rcvinfo(fp, (struct sctp_rcvinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_NXTINFO:
		if (len == CMSG_LEN(sizeof(struct sctp_nxtinfo)))
			print_sctp_nxtinfo(fp, (struct sctp_nxtinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_PRINFO:
		if (len == CMSG_LEN(sizeof(struct sctp_prinfo)))
			print_sctp_prinfo(fp, (struct sctp_prinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_AUTHINFO:
		if (len == CMSG_LEN(sizeof(struct sctp_authinfo)))
			print_sctp_authinfo(fp, (struct sctp_authinfo *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_DSTADDRV4:
		if (len == CMSG_LEN(sizeof(struct in_addr)))
			print_sctp_ipv4_addr(fp, (struct in_addr *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	case SCTP_DSTADDRV6:
		if (len == CMSG_LEN(sizeof(struct in6_addr)))
			print_sctp_ipv6_addr(fp, (struct in6_addr *)data);
		else
			print_gen_cmsg(fp, cmsghdr);
		break;
	default:
		print_gen_cmsg(fp, cmsghdr);
	}
}