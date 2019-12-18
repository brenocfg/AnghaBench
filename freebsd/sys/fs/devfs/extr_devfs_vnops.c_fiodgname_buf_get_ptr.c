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
typedef  int u_long ;
struct fiodgname_arg32 {int /*<<< orphan*/  buf; } ;
struct fiodgname_arg {void* buf; } ;

/* Variables and functions */
#define  FIODGNAME 129 
#define  FIODGNAME_32 128 
 int /*<<< orphan*/  panic (char*,int) ; 

void *
fiodgname_buf_get_ptr(void *fgnp, u_long com)
{
	union {
		struct fiodgname_arg	fgn;
#ifdef COMPAT_FREEBSD32
		struct fiodgname_arg32	fgn32;
#endif
	} *fgnup;

	fgnup = fgnp;
	switch (com) {
	case FIODGNAME:
		return (fgnup->fgn.buf);
#ifdef COMPAT_FREEBSD32
	case FIODGNAME_32:
		return ((void *)(uintptr_t)fgnup->fgn32.buf);
#endif
	default:
		panic("Unhandled ioctl command %ld", com);
	}
}