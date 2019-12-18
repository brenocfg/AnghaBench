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
typedef  int /*<<< orphan*/  u_int ;
struct ccport {scalar_t__ admin; int /*<<< orphan*/  uarg; } ;
struct ccdata {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_uni_glob ) (struct ccport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ CCPORT_RUNNING ; 
 scalar_t__ CCPORT_STOPPED ; 
 int EISCONN ; 
 int ENOENT ; 
 int /*<<< orphan*/  UNIAPI_LINK_ESTABLISH_request ; 
 struct ccport* find_port (struct ccdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ccport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
cc_port_start(struct ccdata *cc, u_int portno)
{
	struct ccport *port;

	if ((port = find_port(cc, portno)) == NULL)
		return (ENOENT);
	if (port->admin != CCPORT_STOPPED)
		return (EISCONN);

	cc->funcs->send_uni_glob(port, port->uarg,
	    UNIAPI_LINK_ESTABLISH_request, 0, NULL);
	port->admin = CCPORT_RUNNING;

	return (0);
}