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
typedef  scalar_t__ uintmax_t ;
struct printf_info {char spec; int alt; int is_long_double; } ;
struct __printf_io {int dummy; } ;

/* Variables and functions */
 int __printf_render_int (struct __printf_io*,struct printf_info*,void const**) ; 

int
__printf_render_ptr(struct __printf_io *io, const struct printf_info *pi, const void *const *arg)
{
	struct printf_info p2;
	uintmax_t u;
	const void *p;

	/*-
	 * ``The argument shall be a pointer to void.  The
	 * value of the pointer is converted to a sequence
	 * of printable characters, in an implementation-
	 * defined manner.''
	 *      -- ANSI X3J11
	 */
	u = (uintmax_t)(uintptr_t) *((void **)arg[0]);
	p2 = *pi;

	p2.spec = 'x';
	p2.alt = 1;
	p2.is_long_double = 1;
	p = &u;
	return (__printf_render_int(io, &p2, &p));
}