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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct l_sockaddr {int sa_family; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int UCHAR_MAX ; 
 int /*<<< orphan*/  bcopy (struct sockaddr const*,struct l_sockaddr*,int) ; 
 int bsd_to_linux_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct l_sockaddr*,int /*<<< orphan*/ ) ; 
 struct l_sockaddr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bsd_to_linux_sockaddr(const struct sockaddr *sa, struct l_sockaddr **lsa,
    socklen_t len)
{
	struct l_sockaddr *kosa;
	int error, bdom;

	*lsa = NULL;
	if (len < 2 || len > UCHAR_MAX)
		return (EINVAL);

	kosa = malloc(len, M_SONAME, M_WAITOK);
	bcopy(sa, kosa, len);

	bdom = bsd_to_linux_domain(sa->sa_family);
	if (bdom == -1) {
		error = EAFNOSUPPORT;
		goto out;
	}

	kosa->sa_family = bdom;
	*lsa = kosa;
	return (0);

out:
	free(kosa, M_SONAME);
	return (error);
}