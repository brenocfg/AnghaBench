#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int off_t ;
struct TYPE_4__ {int x_op; scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_5__ {int out_finger; int out_base; int in_boundry; int in_finger; scalar_t__ tcp_handle; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
#define  XDR_DECODE 129 
#define  XDR_ENCODE 128 
 int lseek (int,int,int) ; 

__attribute__((used)) static u_int
xdrrec_getpos(XDR *xdrs)
{
	RECSTREAM *rstrm = (RECSTREAM *)xdrs->x_private;
	off_t pos;

	pos = lseek((int)(u_long)rstrm->tcp_handle, (off_t)0, 1);
	if (pos == -1)
		pos = 0;
	switch (xdrs->x_op) {

	case XDR_ENCODE:
		pos += rstrm->out_finger - rstrm->out_base;
		break;

	case XDR_DECODE:
		pos -= rstrm->in_boundry - rstrm->in_finger;
		break;

	default:
		pos = (off_t) -1;
		break;
	}
	return ((u_int) pos);
}