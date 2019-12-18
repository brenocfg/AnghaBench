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
struct ntb_child {int mwcnt; int mwoff; int spadcnt; int spadoff; int dbcnt; int dboff; int function; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bus_print_child_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int) ; 

int
ntb_print_child(device_t dev, device_t child)
{
	struct ntb_child *nc = device_get_ivars(child);
	int retval;

	retval = bus_print_child_header(dev, child);
	if (nc->mwcnt > 0) {
		printf(" mw %d", nc->mwoff);
		if (nc->mwcnt > 1)
			printf("-%d", nc->mwoff + nc->mwcnt - 1);
	}
	if (nc->spadcnt > 0) {
		printf(" spad %d", nc->spadoff);
		if (nc->spadcnt > 1)
			printf("-%d", nc->spadoff + nc->spadcnt - 1);
	}
	if (nc->dbcnt > 0) {
		printf(" db %d", nc->dboff);
		if (nc->dbcnt > 1)
			printf("-%d", nc->dboff + nc->dbcnt - 1);
	}
	retval += printf(" at function %d", nc->function);
	retval += bus_print_child_domain(dev, child);
	retval += bus_print_child_footer(dev, child);

	return (retval);
}