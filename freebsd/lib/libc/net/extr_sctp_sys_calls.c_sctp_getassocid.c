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
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct sctp_paddrinfo {int /*<<< orphan*/  spinfo_assoc_id; int /*<<< orphan*/  spinfo_address; } ;
typedef  int /*<<< orphan*/  sp ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sctp_assoc_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_GET_PEER_ADDR_INFO ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_paddrinfo*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sctp_paddrinfo*,int /*<<< orphan*/ ,int) ; 

sctp_assoc_t
sctp_getassocid(int sd, struct sockaddr *sa)
{
	struct sctp_paddrinfo sp;
	socklen_t siz;

	/* First get the assoc id */
	siz = sizeof(sp);
	memset(&sp, 0, sizeof(sp));
	memcpy((caddr_t)&sp.spinfo_address, sa, sa->sa_len);
	if (getsockopt(sd, IPPROTO_SCTP,
	    SCTP_GET_PEER_ADDR_INFO, &sp, &siz) != 0) {
		/* We depend on the fact that 0 can never be returned */
		return ((sctp_assoc_t) 0);
	}
	return (sp.spinfo_assoc_id);
}