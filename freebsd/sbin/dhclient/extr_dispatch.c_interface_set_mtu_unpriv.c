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
struct imsg_hdr {int len; int /*<<< orphan*/  code; } ;
typedef  struct imsg_hdr u_int16_t ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  mtu ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  IMSG_SET_INTERFACE_MTU ; 
 scalar_t__ buf_add (struct buf*,struct imsg_hdr*,int) ; 
 int buf_close (int,struct buf*) ; 
 struct buf* buf_open (int) ; 
 int /*<<< orphan*/  error (char*) ; 

void
interface_set_mtu_unpriv(int privfd, u_int16_t mtu)
{
	struct imsg_hdr hdr;
	struct buf *buf;
	int errs = 0;

	hdr.code = IMSG_SET_INTERFACE_MTU;
	hdr.len = sizeof(hdr) +
		sizeof(u_int16_t);

	if ((buf = buf_open(hdr.len)) == NULL)
		error("buf_open: %m");

	errs += buf_add(buf, &hdr, sizeof(hdr));
	errs += buf_add(buf, &mtu, sizeof(mtu));
	if (errs)
		error("buf_add: %m");
	
	if (buf_close(privfd, buf) == -1)
		error("buf_close: %m");
}