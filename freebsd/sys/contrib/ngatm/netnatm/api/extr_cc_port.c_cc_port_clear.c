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
struct ccport {int /*<<< orphan*/  addr_list; } ;
struct ccdata {int dummy; } ;
struct ccaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCFREE (struct ccaddr*) ; 
 int ENOENT ; 
 struct ccaddr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccaddr*,int /*<<< orphan*/ ) ; 
 struct ccport* find_port (struct ccdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_link ; 

int
cc_port_clear(struct ccdata *cc, u_int portno)
{
	struct ccaddr *addr;
	struct ccport *port;

	if ((port = find_port(cc, portno)) == NULL)
		return (ENOENT);

	while ((addr = TAILQ_FIRST(&port->addr_list)) != NULL) {
		TAILQ_REMOVE(&port->addr_list, addr, port_link);
		CCFREE(addr);
	}
	return (0);
}