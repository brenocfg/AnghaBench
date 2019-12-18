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
struct print_buf {char* buf; size_t size; } ;

/* Variables and functions */
 int kvprintf (char const*,int /*<<< orphan*/ *,struct print_buf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprint_func ; 

int
vsnprintf(char *buf, size_t size, const char *cfmt, va_list ap)
{
	struct print_buf arg;
	int retval;

	arg.buf = buf;
	arg.size = size;

	retval = kvprintf(cfmt, &snprint_func, &arg, 10, ap);

	if (arg.size >= 1)
		*(arg.buf)++ = 0;

	return (retval);
}