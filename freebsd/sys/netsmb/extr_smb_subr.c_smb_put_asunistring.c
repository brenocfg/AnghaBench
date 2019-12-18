#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct mbchain {int dummy; } ;
struct smb_rq {TYPE_1__* sr_vc; struct mbchain sr_rq; } ;
struct iconv_drv {int dummy; } ;
struct TYPE_2__ {struct iconv_drv* vc_toserver; } ;

/* Variables and functions */
 int /*<<< orphan*/  iconv_convmem (struct iconv_drv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mb_put_uint16le (struct mbchain*,int /*<<< orphan*/ ) ; 

int
smb_put_asunistring(struct smb_rq *rqp, const char *src)
{
	struct mbchain *mbp = &rqp->sr_rq;
	struct iconv_drv *dp = rqp->sr_vc->vc_toserver;
	u_char c;
	int error;

	while (*src) {
		iconv_convmem(dp, &c, src++, 1);
		error = mb_put_uint16le(mbp, c);
		if (error)
			return error;
	}
	return mb_put_uint16le(mbp, 0);
}