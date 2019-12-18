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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  addto_syslog (int,char*) ; 
 int /*<<< orphan*/  mvsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void
mvsyslog(
	int		level,
	const char *	fmt,
	va_list		ap
	)
{
	char	buf[1024];
	mvsnprintf(buf, sizeof(buf), fmt, ap);
	addto_syslog(level, buf);
}