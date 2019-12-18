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
struct atm_port_info {int dummy; } ;
struct ccport {struct atm_port_info param; } ;
struct ccdata {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ccport* find_port (struct ccdata*,int /*<<< orphan*/ ) ; 

int
cc_port_get_param(struct ccdata *cc, u_int portno,
    struct atm_port_info *param)
{
	struct ccport *port;

	if ((port = find_port(cc, portno)) == NULL)
		return (ENOENT);

	*param = port->param;
	return (0);
}