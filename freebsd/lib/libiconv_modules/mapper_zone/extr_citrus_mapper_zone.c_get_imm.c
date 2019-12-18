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
struct _parse_state {unsigned long ps_u_imm; } ;
struct _memstream {int dummy; } ;

/* Variables and functions */
 int BUFSIZE ; 
 int T_ERR ; 
 int T_IMM ; 
 int /*<<< orphan*/  _bcs_isdigit (int) ; 
 int /*<<< orphan*/  _bcs_isxdigit (int) ; 
 char _memstream_getc (struct _memstream*) ; 
 int _memstream_peek (struct _memstream*) ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_imm(struct _memstream *ms, struct _parse_state *ps)
{
	int c, i, sign = 0;
	char buf[BUFSIZE + 1];
	char *p;

	for (i = 0; i < BUFSIZE; i++) {
retry:
		c = _memstream_peek(ms);
		if (i == 0) {
			if (sign == 0 && (c == '+' || c == '-')) {
				sign = c;
				_memstream_getc(ms);
				goto retry;
			} else if (!_bcs_isdigit(c))
				break;
		} else if (!_bcs_isxdigit(c))
			if (!(i == 1 && c == 'x'))
				break;
		buf[i] = _memstream_getc(ms);
	}
	buf[i] = '\0';
	ps->ps_u_imm = strtoul(buf, &p, 0);
	if ((p - buf) != i)
		return (T_ERR);
	if (sign == '-')
		ps->ps_u_imm = (unsigned long)-(long)ps->ps_u_imm;
	return (T_IMM);
}