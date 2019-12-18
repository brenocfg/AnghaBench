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
struct uio {int uio_iovcnt; TYPE_1__* uio_iov; } ;
struct TYPE_2__ {int iov_len; } ;

/* Variables and functions */

int
cuio_getptr(struct uio *uio, int loc, int *off)
{
	int ind, len;

	ind = 0;
	while (loc >= 0 && ind < uio->uio_iovcnt) {
		len = uio->uio_iov[ind].iov_len;
		if (len > loc) {
	    		*off = loc;
	    		return (ind);
		}
		loc -= len;
		ind++;
	}

	if (ind > 0 && loc == 0) {
		ind--;
		*off = uio->uio_iov[ind].iov_len;
		return (ind);
	}

	return (-1);
}