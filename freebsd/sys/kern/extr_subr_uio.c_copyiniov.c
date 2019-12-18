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
typedef  int u_int ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int UIO_MAXIOV ; 
 int copyin (struct iovec const*,struct iovec*,int) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
copyiniov(const struct iovec *iovp, u_int iovcnt, struct iovec **iov, int error)
{
	u_int iovlen;

	*iov = NULL;
	if (iovcnt > UIO_MAXIOV)
		return (error);
	iovlen = iovcnt * sizeof (struct iovec);
	*iov = malloc(iovlen, M_IOV, M_WAITOK);
	error = copyin(iovp, *iov, iovlen);
	if (error) {
		free(*iov, M_IOV);
		*iov = NULL;
	}
	return (error);
}