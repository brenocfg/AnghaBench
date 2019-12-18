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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  proc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int LOGMSG_SIZE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ uc_cfg ; 
 int /*<<< orphan*/  uc_output (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void
uc_vlogmsgx(const char *format, va_list ap)
{
	char buf[LOGMSG_SIZE];

	if (vsnprintf(buf, sizeof(buf), format, ap) < 0)
		err(EXIT_FAILURE, "uc_logmsgx: vsnprintf failed");
	uc_output("%s: %s\n", uc_cfg.proc_name, buf);
}