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
struct snprintf_arg {scalar_t__ remain; scalar_t__ buf_total; int /*<<< orphan*/  buf; int /*<<< orphan*/  str; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
printf_out(struct snprintf_arg *info)
{

	if (info->remain == info->buf_total)
		return;
	write(info->fd, info->buf, info->buf_total - info->remain);
	info->str = info->buf;
	info->remain = info->buf_total;
}