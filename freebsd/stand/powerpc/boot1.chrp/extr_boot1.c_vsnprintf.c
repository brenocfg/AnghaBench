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
struct sp_data {char* sp_buf; size_t sp_size; scalar_t__ sp_len; } ;

/* Variables and functions */
 int __printf (char const*,int /*<<< orphan*/ ,struct sp_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sputc ; 

__attribute__((used)) static int
vsnprintf(char *str, size_t sz, const char *fmt, va_list ap)
{
	struct sp_data sp;
	int ret;

	sp.sp_buf = str;
	sp.sp_len = 0;
	sp.sp_size = sz;
	ret = __printf(fmt, __sputc, &sp, ap);
	return (ret);
}