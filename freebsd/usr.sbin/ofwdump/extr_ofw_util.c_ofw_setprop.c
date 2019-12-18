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
struct ofiocdesc {char const* of_name; int of_buflen; int /*<<< orphan*/  of_buf; int /*<<< orphan*/  of_namelen; int /*<<< orphan*/  of_nodeid; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFIOCSET ; 
 int /*<<< orphan*/  OFW_IOCTL (int,int /*<<< orphan*/ ,struct ofiocdesc*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  ofw_malloc (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
ofw_setprop(int fd, phandle_t node, const char *name, const void *buf,
    int buflen)
{
	struct ofiocdesc d;

	d.of_nodeid = node;
	d.of_namelen = strlen(name);
	d.of_name = name;
	d.of_buflen = buflen;
	d.of_buf = ofw_malloc(buflen);
	memcpy(d.of_buf, buf, buflen);
	OFW_IOCTL(fd, OFIOCSET, &d);
	free(d.of_buf);
	return (d.of_buflen);
}