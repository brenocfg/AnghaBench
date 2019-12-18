#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  scalar_t__ wchar_t ;
struct __suio {size_t uio_resid; int uio_iovcnt; struct __siov* uio_iov; } ;
struct __siov {char* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_5__ {int _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  WEOF ; 
 int __SERR ; 
 int __SSTR ; 
 int /*<<< orphan*/  __fputwc (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __sfvwrite (TYPE_1__*,struct __suio*) ; 
 int /*<<< orphan*/  initial_mbs ; 
 size_t wcrtomb (char*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static wint_t
__xfputwc(wchar_t wc, FILE *fp, locale_t locale)
{
	mbstate_t mbs;
	char buf[MB_LEN_MAX];
	struct __suio uio;
	struct __siov iov;
	size_t len;

	if ((fp->_flags & __SSTR) == 0)
		return (__fputwc(wc, fp, locale));

	mbs = initial_mbs;
	if ((len = wcrtomb(buf, wc, &mbs)) == (size_t)-1) {
		fp->_flags |= __SERR;
		return (WEOF);
	}
	uio.uio_iov = &iov;
	uio.uio_resid = len;
	uio.uio_iovcnt = 1;
	iov.iov_base = buf;
	iov.iov_len = len;
	return (__sfvwrite(fp, &uio) != EOF ? (wint_t)wc : WEOF);
}