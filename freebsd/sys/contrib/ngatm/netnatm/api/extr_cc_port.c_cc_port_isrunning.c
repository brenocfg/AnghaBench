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
typedef  int /*<<< orphan*/  u_int ;
struct ccport {scalar_t__ admin; } ;
struct ccdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCPORT_RUNNING ; 
 int ENOENT ; 
 struct ccport* find_port (struct ccdata*,int /*<<< orphan*/ ) ; 

int
cc_port_isrunning(struct ccdata *cc, u_int portno, int *state)
{
	struct ccport *port;

	if ((port = find_port(cc, portno)) == NULL)
		return (ENOENT);
	if (port->admin == CCPORT_RUNNING)
		*state = 1;
	else
		*state = 0;
	return (0);
}