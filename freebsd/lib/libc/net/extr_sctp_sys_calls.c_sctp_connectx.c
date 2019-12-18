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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; int sa_len; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sctp_assoc_t ;
typedef  int caddr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_CONNECT_X ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,struct sockaddr const*,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int
sctp_connectx(int sd, const struct sockaddr *addrs, int addrcnt,
    sctp_assoc_t * id)
{
	char *buf;
	int i, ret, *aa;
	char *cpto;
	const struct sockaddr *at;
	size_t len;

	/* validate the address count and list */
	if ((addrs == NULL) || (addrcnt <= 0)) {
		errno = EINVAL;
		return (-1);
	}
	if ((buf = malloc(sizeof(int) + (size_t)addrcnt * sizeof(struct sockaddr_in6))) == NULL) {
		errno = E2BIG;
		return (-1);
	}
	len = sizeof(int);
	at = addrs;
	cpto = buf + sizeof(int);
	/* validate all the addresses and get the size */
	for (i = 0; i < addrcnt; i++) {
		switch (at->sa_family) {
		case AF_INET:
			if (at->sa_len != sizeof(struct sockaddr_in)) {
				free(buf);
				errno = EINVAL;
				return (-1);
			}
			memcpy(cpto, at, sizeof(struct sockaddr_in));
			cpto = ((caddr_t)cpto + sizeof(struct sockaddr_in));
			len += sizeof(struct sockaddr_in);
			break;
		case AF_INET6:
			if (at->sa_len != sizeof(struct sockaddr_in6)) {
				free(buf);
				errno = EINVAL;
				return (-1);
			}
			if (IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)at)->sin6_addr)) {
				in6_sin6_2_sin((struct sockaddr_in *)cpto, (struct sockaddr_in6 *)at);
				cpto = ((caddr_t)cpto + sizeof(struct sockaddr_in));
				len += sizeof(struct sockaddr_in);
			} else {
				memcpy(cpto, at, sizeof(struct sockaddr_in6));
				cpto = ((caddr_t)cpto + sizeof(struct sockaddr_in6));
				len += sizeof(struct sockaddr_in6);
			}
			break;
		default:
			free(buf);
			errno = EINVAL;
			return (-1);
		}
		at = (struct sockaddr *)((caddr_t)at + at->sa_len);
	}
	aa = (int *)buf;
	*aa = addrcnt;
	ret = setsockopt(sd, IPPROTO_SCTP, SCTP_CONNECT_X, (void *)buf,
	    (socklen_t) len);
	if ((ret == 0) && (id != NULL)) {
		*id = *(sctp_assoc_t *) buf;
	}
	free(buf);
	return (ret);
}