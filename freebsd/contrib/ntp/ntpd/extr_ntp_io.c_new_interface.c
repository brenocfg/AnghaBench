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
struct interface {int /*<<< orphan*/  starttime; scalar_t__ ifnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_EMERG ; 
 int /*<<< orphan*/  current_time ; 
 struct interface* emalloc (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  init_interface (struct interface*) ; 
 int /*<<< orphan*/  io_completion_port_add_interface (struct interface*) ; 
 int /*<<< orphan*/  memcpy (struct interface*,struct interface*,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sys_ifnum ; 

__attribute__((used)) static struct interface *
new_interface(
	struct interface *interface
	)
{
	struct interface *	iface;

	iface = emalloc(sizeof(*iface));

	if (NULL == interface)
		init_interface(iface);
	else				/* use the template */
		memcpy(iface, interface, sizeof(*iface));

	/* count every new instance of an interface in the system */
	iface->ifnum = sys_ifnum++;
	iface->starttime = current_time;

#   ifdef HAVE_IO_COMPLETION_PORT
	if (!io_completion_port_add_interface(iface)) {
		msyslog(LOG_EMERG, "cannot register interface with IO engine -- will exit now");
		exit(1);
	}
#   endif
	return iface;
}