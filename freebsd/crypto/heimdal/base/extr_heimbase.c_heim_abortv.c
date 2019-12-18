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
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void
heim_abortv(const char *fmt, va_list ap)
{
    static char str[1024];

    vsnprintf(str, sizeof(str), fmt, ap);
    syslog(LOG_ERR, "heim_abort: %s", str);
    abort();
}