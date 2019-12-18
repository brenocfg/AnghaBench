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
typedef  int u_int ;
struct TYPE_2__ {scalar_t__ cmdlist; } ;

/* Variables and functions */
 int EVENT_MAX ; 
 int /*<<< orphan*/  apmctl_fd ; 
 int /*<<< orphan*/  apmd_configfile ; 
 int /*<<< orphan*/  debug_level ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 TYPE_1__* events ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  yydebug ; 
 int /*<<< orphan*/ * yyin ; 
 scalar_t__ yyparse () ; 

void
read_config(void)
{
	int i;

	if ((yyin = fopen(apmd_configfile, "r")) == NULL) {
		err(1, "cannot open config file");
	}

#ifdef DEBUG
	yydebug = debug_level;
#endif

	if (yyparse() != 0)
		err(1, "cannot parse config file");

	fclose(yyin);

	/* enable events */
	for (i = 0; i < EVENT_MAX; i++) {
		if (events[i].cmdlist) {
			u_int event_type = i;
			if (write(apmctl_fd, &event_type, sizeof(u_int)) == -1) {
				err(1, "cannot enable event 0x%x", event_type);
			}
		}
	}
}