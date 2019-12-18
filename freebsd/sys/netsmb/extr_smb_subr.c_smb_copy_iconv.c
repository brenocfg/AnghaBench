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
struct mbchain {scalar_t__ mb_udata; } ;
struct iconv_drv {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  c_caddr_t ;

/* Variables and functions */
 int iconv_conv (struct iconv_drv*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
smb_copy_iconv(struct mbchain *mbp, c_caddr_t src, caddr_t dst,
    size_t *srclen, size_t *dstlen)
{
	int error;
	size_t inlen = *srclen, outlen = *dstlen;

	error = iconv_conv((struct iconv_drv*)mbp->mb_udata, &src, &inlen,
	    &dst, &outlen);
	if (inlen != *srclen || outlen != *dstlen) {
		*srclen -= inlen;
		*dstlen -= outlen;
		return 0;
	} else
		return error;
}