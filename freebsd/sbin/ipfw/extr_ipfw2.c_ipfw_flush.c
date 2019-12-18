#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rt ;
struct TYPE_5__ {scalar_t__ set; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_range_tlv ;
struct TYPE_6__ {scalar_t__ use_set; scalar_t__ do_pipe; int /*<<< orphan*/  do_quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  IPFW_RCFLAG_ALL ; 
 int /*<<< orphan*/  IPFW_RCFLAG_SET ; 
 int /*<<< orphan*/  IP_FW_XDEL ; 
 TYPE_4__ co ; 
 scalar_t__ do_range_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dummynet_flush () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int toupper (char) ; 

void
ipfw_flush(int force)
{
	ipfw_range_tlv rt;

	if (!force && !co.do_quiet) { /* need to ask user */
		int c;

		printf("Are you sure? [yn] ");
		fflush(stdout);
		do {
			c = toupper(getc(stdin));
			while (c != '\n' && getc(stdin) != '\n')
				if (feof(stdin))
					return; /* and do not flush */
		} while (c != 'Y' && c != 'N');
		printf("\n");
		if (c == 'N')	/* user said no */
			return;
	}
	if (co.do_pipe) {
		dummynet_flush();
		return;
	}
	/* `ipfw set N flush` - is the same that `ipfw delete set N` */
	memset(&rt, 0, sizeof(rt));
	if (co.use_set != 0) {
		rt.set = co.use_set - 1;
		rt.flags = IPFW_RCFLAG_SET;
	} else
		rt.flags = IPFW_RCFLAG_ALL;
	if (do_range_cmd(IP_FW_XDEL, &rt) != 0)
			err(EX_UNAVAILABLE, "setsockopt(IP_FW_XDEL)");
	if (!co.do_quiet)
		printf("Flushed all %s.\n", co.do_pipe ? "pipes" : "rules");
}