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
struct sctp_assoc_value {scalar_t__ assoc_value; } ;
typedef  int socklen_t ;
typedef  scalar_t__ sa_family_t ;
typedef  int /*<<< orphan*/  av ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_GET_ADDR_LEN ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  close (int) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_assoc_value*,int*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sctp_getaddrlen(sa_family_t family)
{
	int ret, sd;
	socklen_t siz;
	struct sctp_assoc_value av;

	av.assoc_value = family;
	siz = sizeof(av);
#if defined(AF_INET)
	sd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
#elif defined(AF_INET6)
	sd = socket(AF_INET6, SOCK_SEQPACKET, IPPROTO_SCTP);
#else
	sd = -1;
#endif
	if (sd == -1) {
		return (-1);
	}
	ret = getsockopt(sd, IPPROTO_SCTP, SCTP_GET_ADDR_LEN, &av, &siz);
	close(sd);
	if (ret == 0) {
		return ((int)av.assoc_value);
	} else {
		return (-1);
	}
}