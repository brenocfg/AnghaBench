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
struct ofiocdesc {char const* of_name; int of_buflen; void* of_buf; int /*<<< orphan*/  of_namelen; int /*<<< orphan*/  of_nodeid; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFIOCGET ; 
 int /*<<< orphan*/  OFW_IOCTL (int,int /*<<< orphan*/ ,struct ofiocdesc*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
ofw_getprop(int fd, phandle_t node, const char *name, void *buf, int buflen)
{
	struct ofiocdesc d;

	d.of_nodeid = node;
	d.of_namelen = strlen(name);
	d.of_name = name;
	d.of_buflen = buflen;
	d.of_buf = buf;
	OFW_IOCTL(fd, OFIOCGET, &d);
	return (d.of_buflen);
}