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
typedef  int /*<<< orphan*/  wchar_t ;
struct __suio {scalar_t__ uio_resid; scalar_t__ uio_iovcnt; struct __siov* uio_iov; } ;
struct __siov {int iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ WEOF ; 
 scalar_t__ __xfputwc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__sprint(FILE *fp, struct __suio *uio, locale_t locale)
{
	struct __siov *iov;
	wchar_t *p;
	int i, len;

	iov = uio->uio_iov;
	for (; uio->uio_resid != 0; uio->uio_resid -= len, iov++) {
		p = (wchar_t *)iov->iov_base;
		len = iov->iov_len;
		for (i = 0; i < len; i++) {
			if (__xfputwc(p[i], fp, locale) == WEOF)
				return (-1);
		}
	}
	uio->uio_iovcnt = 0;
	return (0);
}