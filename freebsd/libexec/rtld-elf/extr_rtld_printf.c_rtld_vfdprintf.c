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
struct snprintf_arg {char* buf; char* str; int buf_total; int remain; int fd; int /*<<< orphan*/  method; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_METHOD_WRITE ; 
 int kvprintf (char const*,struct snprintf_arg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_out (struct snprintf_arg*) ; 

int
rtld_vfdprintf(int fd, const char *fmt, va_list ap)
{
	char buf[512];
	struct snprintf_arg info;
	int retval;

	info.method = PRINT_METHOD_WRITE;
	info.buf = info.str = buf;
	info.buf_total = info.remain = sizeof(buf);
	info.fd = fd;
	retval = kvprintf(fmt, &info, 10, ap);
	printf_out(&info);
	return (retval);
}