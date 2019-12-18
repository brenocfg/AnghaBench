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
struct inout_port {char* name; int port; int size; int flags; int /*<<< orphan*/  handler; } ;
typedef  int /*<<< orphan*/  iop ;

/* Variables and functions */
 int IOPORT_F_DEFAULT ; 
 int IOPORT_F_INOUT ; 
 int /*<<< orphan*/  VERIFY_IOPORT (int,int) ; 
 int /*<<< orphan*/  bzero (struct inout_port*,int) ; 
 int /*<<< orphan*/  default_inout ; 
 int /*<<< orphan*/  register_inout (struct inout_port*) ; 

__attribute__((used)) static void 
register_default_iohandler(int start, int size)
{
	struct inout_port iop;
	
	VERIFY_IOPORT(start, size);

	bzero(&iop, sizeof(iop));
	iop.name = "default";
	iop.port = start;
	iop.size = size;
	iop.flags = IOPORT_F_INOUT | IOPORT_F_DEFAULT;
	iop.handler = default_inout;

	register_inout(&iop);
}