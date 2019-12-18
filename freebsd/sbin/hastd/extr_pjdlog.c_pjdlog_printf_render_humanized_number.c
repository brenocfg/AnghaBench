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
struct printf_info {int dummy; } ;
struct __printf_io {int dummy; } ;
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  __printf_flush (struct __printf_io*) ; 
 int __printf_out (struct __printf_io*,struct printf_info const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
pjdlog_printf_render_humanized_number(struct __printf_io *io,
    const struct printf_info *pi, const void * const *arg)
{
	char buf[5];
	intmax_t num;
	int ret;

	num = *(const intmax_t *)arg[0];
	humanize_number(buf, sizeof(buf), (int64_t)num, "", HN_AUTOSCALE,
	    HN_NOSPACE | HN_DECIMAL);
	ret = __printf_out(io, pi, buf, strlen(buf));
	__printf_flush(io);
	return (ret);
}