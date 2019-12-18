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
typedef  scalar_t__ u_char ;
struct dcons_state {int flags; int escape_state; scalar_t__ escape; int /*<<< orphan*/  reset; } ;
struct dcons_port {int skip_read; int /*<<< orphan*/  outfd; } ;

/* Variables and functions */
 scalar_t__ CTRL (char) ; 
 int F_ALT_BREAK ; 
 int F_TELNET ; 
 scalar_t__ IAC ; 
 scalar_t__ IS_CONSOLE (struct dcons_port*) ; 
 scalar_t__ IS_GDB (struct dcons_port*) ; 
 scalar_t__ KEY_CR ; 
 void* STATE0 ; 
#define  STATE1 130 
#define  STATE2 129 
#define  STATE3 128 
 int /*<<< orphan*/  abreak ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  dconschat_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconschat_fork_gdb (struct dcons_state*,struct dcons_port*) ; 
 int /*<<< orphan*/  dconschat_reset_target (struct dcons_state*,struct dcons_port*) ; 
 int /*<<< orphan*/  dconschat_suspend (struct dcons_state*,struct dcons_port*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int strlen (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
dconschat_read_filter(struct dcons_state *dc, struct dcons_port *p,
    u_char *sp, int slen, u_char *dp, int *dlen)
{
	int skip;
	char *buf;

	while (slen > 0) {
		skip = 0;
		if (IS_CONSOLE(p)) {
			if ((dc->flags & F_TELNET) != 0) {
				/* XXX Telnet workarounds */
				if (p->skip_read -- > 0) {
					sp ++;
					slen --;
					continue;
				}
				if (*sp == IAC) {
					if (verbose)
						printf("(IAC)");
					p->skip_read = 2;
					sp ++;
					slen --;
					continue;
				}
				if (*sp == 0) {
					if (verbose)
						printf("(0 stripped)");
					sp ++;
					slen --;
					continue;
				}
			}
			switch (dc->escape_state) {
			case STATE1:
				if (*sp == dc->escape) {
					skip = 1;
					dc->escape_state = STATE2;
				} else
					dc->escape_state = STATE0;
				break;
			case STATE2:
				dc->escape_state = STATE0;
				skip = 1;
				if (*sp == '.')
					dconschat_cleanup(0);
				else if (*sp == CTRL('B')) {
					bcopy(abreak, dp, 3);
					dp += 3;
					*dlen += 3;
				}
				else if (*sp == CTRL('G'))
					dconschat_fork_gdb(dc, p);
				else if ((*sp == CTRL('R'))
						&& (dc->reset != 0)) {
					dc->escape_state = STATE3;
					buf = "\r\n[Are you sure to reset target? (y/N)]";
					write(p->outfd, buf, strlen(buf));
				} else if (*sp == CTRL('Z'))
					dconschat_suspend(dc, p);
				else {
					skip = 0;
					*dp++ = dc->escape;
					(*dlen) ++;
				}
				break;
			case STATE3:
				dc->escape_state = STATE0;
				skip = 1;
				if (*sp == 'y')
					dconschat_reset_target(dc, p);
				else {
					write(p->outfd, sp, 1);
					write(p->outfd, "\r\n", 2);
				}
				break;
			}
			if (*sp == KEY_CR)
				dc->escape_state = STATE1;
		} else if (IS_GDB(p)) {
			/* GDB: ^C -> CR+~+^B */
			if (*sp == CTRL('C') && (dc->flags & F_ALT_BREAK) != 0) {
				bcopy(abreak, dp, 3);
				dp += 3;
				sp ++;
				*dlen += 3;
				/* discard rest of the packet */
				slen = 0;
				break;
			}
		}
		if (!skip) {
			*dp++ = *sp;
			(*dlen) ++;
		}
		sp ++;
		slen --;
	}
	return (*dlen);
			
}