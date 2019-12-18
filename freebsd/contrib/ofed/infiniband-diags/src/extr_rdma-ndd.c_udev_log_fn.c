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
struct udev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int MSG_MAX ; 
 int snprintf (char*,int,char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udev_log_fn(struct udev *ud, int priority, const char *file, int line,
		const char *fn, const char *format, va_list args)
{
	int off = 0;
	char msg[MSG_MAX];
	off = snprintf(msg, MSG_MAX, "libudev: %s:%d %s",
			file, line, fn);
	if (off < MSG_MAX-1)
		vsnprintf(msg+off, MSG_MAX-off, format, args);
	syslog(LOG_ERR, msg);
}