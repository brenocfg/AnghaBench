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
struct uio {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int cuio_apply (struct uio*,int,int,int (*) (void*,void*,u_int),void*) ; 
 int m_apply (struct mbuf*,int,int,int (*) (void*,void*,u_int),void*) ; 
 int stub1 (void*,void*,...) ; 

int
crypto_apply(int flags, caddr_t buf, int off, int len,
    int (*f)(void *, void *, u_int), void *arg)
{
	int error;

	if ((flags & CRYPTO_F_IMBUF) != 0)
		error = m_apply((struct mbuf *)buf, off, len, f, arg);
	else if ((flags & CRYPTO_F_IOV) != 0)
		error = cuio_apply((struct uio *)buf, off, len, f, arg);
	else
		error = (*f)(arg, buf + off, len);
	return (error);
}