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
struct __suio {scalar_t__ uio_resid; int uio_iovcnt; struct __siov* uio_iov; } ;
struct __siov {scalar_t__ iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  ORIENT (int /*<<< orphan*/ *,int) ; 
 int __sfvwrite (int /*<<< orphan*/ *,struct __suio*) ; 
 scalar_t__ strlen (char const*) ; 

int
fputs(const char * __restrict s, FILE * __restrict fp)
{
	int retval;
	struct __suio uio;
	struct __siov iov;

	iov.iov_base = (void *)s;
	uio.uio_resid = iov.iov_len = strlen(s);
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	FLOCKFILE_CANCELSAFE(fp);
	ORIENT(fp, -1);
	retval = __sfvwrite(fp, &uio);
	FUNLOCKFILE_CANCELSAFE();
	if (retval == 0)
		return (iov.iov_len > INT_MAX ? INT_MAX : iov.iov_len);
	return (retval);
}