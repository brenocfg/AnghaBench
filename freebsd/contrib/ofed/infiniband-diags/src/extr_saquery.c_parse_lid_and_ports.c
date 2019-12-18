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
struct sa_handle {int dummy; } ;

/* Variables and functions */
 int get_lid (struct sa_handle*,char*) ; 
 char* strchr (char*,char) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_lid_and_ports(struct sa_handle * h,
			       char *str, int *lid, int *port1, int *port2)
{
	char *p, *e;

	if (port1)
		*port1 = -1;
	if (port2)
		*port2 = -1;

	p = strchr(str, '/');
	if (p)
		*p = '\0';
	if (lid)
		*lid = get_lid(h, str);

	if (!p)
		return 0;
	str = p + 1;
	p = strchr(str, '/');
	if (p)
		*p = '\0';
	if (port1) {
		*port1 = strtoul(str, &e, 0);
		if (e == str)
			*port1 = -1;
	}

	if (!p)
		return 0;
	str = p + 1;
	if (port2) {
		*port2 = strtoul(str, &e, 0);
		if (e == str)
			*port2 = -1;
	}

	return 0;
}