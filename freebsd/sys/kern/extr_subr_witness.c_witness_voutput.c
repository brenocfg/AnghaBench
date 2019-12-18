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

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
#define  WITNESS_CONSOLE 130 
#define  WITNESS_LOG 129 
#define  WITNESS_NONE 128 
 int /*<<< orphan*/  vlog (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int vprintf (char const*,int /*<<< orphan*/ ) ; 
 int witness_channel ; 

__attribute__((used)) static int
witness_voutput(const char *fmt, va_list ap)
{
	int ret;

	ret = 0;
	switch (witness_channel) {
	case WITNESS_CONSOLE:
		ret = vprintf(fmt, ap);
		break;
	case WITNESS_LOG:
		vlog(LOG_NOTICE, fmt, ap);
		break;
	case WITNESS_NONE:
		break;
	}
	return (ret);
}