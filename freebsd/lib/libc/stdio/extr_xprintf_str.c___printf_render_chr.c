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
typedef  scalar_t__ wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
struct printf_info {char spec; scalar_t__ is_long; } ;
struct __printf_io {int dummy; } ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  __printf_flush (struct __printf_io*) ; 
 int __printf_out (struct __printf_io*,struct printf_info const*,...) ; 
 size_t wcrtomb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
__printf_render_chr(struct __printf_io *io, const struct printf_info *pi, const void *const *arg)
{
	int i;
	wint_t ii;
	unsigned char c;
	static const mbstate_t initial;		/* XXX: this is bogus! */
	mbstate_t mbs;
	size_t mbseqlen;
	char buf[MB_CUR_MAX];

	if (pi->is_long || pi->spec == 'C') {
		ii = *((wint_t *)arg[0]);

		mbs = initial;
		mbseqlen = wcrtomb(buf, (wchar_t)ii, &mbs);
		if (mbseqlen == (size_t) -1)
			return (-1);
		return (__printf_out(io, pi, buf, mbseqlen));
	}
	i = *((int *)arg[0]);
	c = i;
	i = __printf_out(io, pi, &c, 1);
	__printf_flush(io);
	return (i);
}