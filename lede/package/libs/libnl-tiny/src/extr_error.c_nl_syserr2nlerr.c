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

/* Variables and functions */
#define  EACCES 149 
#define  EADDRINUSE 148 
#define  EADDRNOTAVAIL 147 
#define  EAFNOSUPPORT 146 
#define  EAGAIN 145 
#define  EBADF 144 
#define  EBUSY 143 
#define  EEXIST 142 
#define  EFAULT 141 
#define  EINTR 140 
#define  EINVAL 139 
#define  ENOBUFS 138 
#define  ENODEV 137 
#define  ENOENT 136 
#define  ENOMEM 135 
#define  ENOPROTOOPT 134 
#define  ENOTSOCK 133 
#define  EOPNOTSUPP 132 
#define  EPERM 131 
#define  EPROTONOSUPPORT 130 
#define  ERANGE 129 
#define  ESRCH 128 
 int NLE_AF_NOSUPPORT ; 
 int NLE_AGAIN ; 
 int NLE_BAD_SOCK ; 
 int NLE_BUSY ; 
 int NLE_EXIST ; 
 int NLE_FAILURE ; 
 int NLE_INTR ; 
 int NLE_INVAL ; 
 int NLE_NOACCESS ; 
 int NLE_NOADDR ; 
 int NLE_NODEV ; 
 int NLE_NOMEM ; 
 int NLE_OBJ_NOTFOUND ; 
 int NLE_OPNOTSUPP ; 
 int NLE_PERM ; 
 int NLE_PROTO_MISMATCH ; 
 int NLE_RANGE ; 
 int abs (int) ; 

int nl_syserr2nlerr(int error)
{
	error = abs(error);

	switch (error) {
	case EBADF:		return NLE_BAD_SOCK;
	case EADDRINUSE:	return NLE_EXIST;
	case EEXIST:		return NLE_EXIST;
	case EADDRNOTAVAIL:	return NLE_NOADDR;
	case ESRCH:		/* fall through */
	case ENOENT:		return NLE_OBJ_NOTFOUND;
	case EINTR:		return NLE_INTR;
	case EAGAIN:		return NLE_AGAIN;
	case ENOTSOCK:		return NLE_BAD_SOCK;
	case ENOPROTOOPT:	return NLE_INVAL;
	case EFAULT:		return NLE_INVAL;
	case EACCES:		return NLE_NOACCESS;
	case EINVAL:		return NLE_INVAL;
	case ENOBUFS:		return NLE_NOMEM;
	case ENOMEM:		return NLE_NOMEM;
	case EAFNOSUPPORT:	return NLE_AF_NOSUPPORT;
	case EPROTONOSUPPORT:	return NLE_PROTO_MISMATCH;
	case EOPNOTSUPP:	return NLE_OPNOTSUPP;
	case EPERM:		return NLE_PERM;
	case EBUSY:		return NLE_BUSY;
	case ERANGE:		return NLE_RANGE;
	case ENODEV:		return NLE_NODEV;
	default:		return NLE_FAILURE;
	}
}