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
struct printf_info {int width; int /*<<< orphan*/  pad; scalar_t__ left; } ;
struct __printf_io {int dummy; } ;

/* Variables and functions */
 scalar_t__ __printf_pad (struct __printf_io*,int,int) ; 
 scalar_t__ __printf_puts (struct __printf_io*,void const*,int) ; 

int
__printf_out(struct __printf_io *io, const struct printf_info *pi, const void *ptr, int len)
{
	int ret = 0;

	if ((!pi->left) && pi->width > len)
		ret += __printf_pad(io, pi->width - len, pi->pad == '0');
	ret += __printf_puts(io, ptr, len);
	if (pi->left && pi->width > len)
		ret += __printf_pad(io, pi->width - len, pi->pad == '0');
	return (ret);
}