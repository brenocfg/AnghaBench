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
struct uio {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int MOUSE_SYS_PACKETSIZE ; 
 int SYSMOUSE_MAXFRAMES ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sysmouse_buffer ; 
 scalar_t__ sysmouse_length ; 
 int /*<<< orphan*/  sysmouse_lock ; 
 int sysmouse_start ; 
 int uiomove (unsigned char*,unsigned int,struct uio*) ; 

__attribute__((used)) static int
sysmouse_buf_read(struct uio *uio, unsigned int length)
{
	unsigned char buf[MOUSE_SYS_PACKETSIZE];
	int error;

	if (sysmouse_buffer == NULL)
		return (ENXIO);
	else if (sysmouse_length == 0)
		return (EWOULDBLOCK);

	memcpy(buf, sysmouse_buffer +
	    sysmouse_start * MOUSE_SYS_PACKETSIZE, MOUSE_SYS_PACKETSIZE);
	sysmouse_start = (sysmouse_start + 1) % SYSMOUSE_MAXFRAMES;
	sysmouse_length--;

	mtx_unlock(&sysmouse_lock);
	error = uiomove(buf, length, uio);
	mtx_lock(&sysmouse_lock);

	return (error);
}