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
struct snprintf_arg {char* buf; char* str; size_t buf_total; size_t remain; int fd; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_METHOD_SNPRINTF ; 
 int kvprintf (char const*,struct snprintf_arg*,int,int /*<<< orphan*/ ) ; 

int
rtld_vsnprintf(char *buf, size_t bufsize, const char *fmt, va_list ap)
{
	struct snprintf_arg info;
	int retval;

	info.method = PRINT_METHOD_SNPRINTF;
	info.buf = info.str = buf;
	info.buf_total = info.remain = bufsize;
	info.fd = -1;
	retval = kvprintf(fmt, &info, 10, ap);
	if (info.remain >= 1)
		*info.str++ = '\0';
	return (retval);
}