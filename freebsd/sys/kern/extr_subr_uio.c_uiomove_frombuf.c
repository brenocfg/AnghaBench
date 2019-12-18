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
struct uio {size_t uio_offset; scalar_t__ uio_resid; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IOSIZE_MAX ; 
 int uiomove (char*,size_t,struct uio*) ; 

int
uiomove_frombuf(void *buf, int buflen, struct uio *uio)
{
	size_t offset, n;

	if (uio->uio_offset < 0 || uio->uio_resid < 0 ||
	    (offset = uio->uio_offset) != uio->uio_offset)
		return (EINVAL);
	if (buflen <= 0 || offset >= buflen)
		return (0);
	if ((n = buflen - offset) > IOSIZE_MAX)
		return (EINVAL);
	return (uiomove((char *)buf + offset, n, uio));
}