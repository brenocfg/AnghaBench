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
struct printf_info {int width; scalar_t__ alt; scalar_t__ showsign; } ;
struct __printf_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __printf_flush (struct __printf_io*) ; 
 scalar_t__ __printf_puts (struct __printf_io*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int
__printf_render_hexdump(struct __printf_io *io, const struct printf_info *pi, const void *const *arg)
{
	unsigned char *p;
	int i;
	unsigned u, l, j, a;
	char buf[100], *q;
	int ret;

	if (pi->width > 0 && pi->width < 16)
		l = pi->width;
	else
		l = 16;
	p = *((unsigned char **)arg[0]);
	i = *((int *)arg[1]);
	if (i < 0)
		i = 0;
	u = i;

	ret = 0;
	a = 0;
	while (u > 0) {
		q = buf;
		if (pi->showsign)
			q += sprintf(q, " %04x", a);
		for (j = 0; j < l && j < u; j++)
			q += sprintf(q, " %02x", p[j]);
		if (pi->alt) {
			for (; j < l; j++)
				q += sprintf(q, "   ");
			q += sprintf(q, "  |");
			for (j = 0; j < l && j < u; j++) {
				if (p[j] < ' ' || p[j] > '~')
					*q++ = '.';
				else
					*q++ = p[j];
			}
			for (; j < l; j++)
				*q++ = ' ';
			*q++ = '|';
		}
		if (l < u)
			j = l;
		else
			j = u;
		p += j;
		u -= j;
		a += j;
		if (u > 0)
			*q++ = '\n';
		ret += __printf_puts(io, buf + 1, q - (buf + 1));
		__printf_flush(io);
	}
	return (ret);
}