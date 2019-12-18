#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* lastbcomm; } ;
struct TYPE_11__ {char* alt_name; TYPE_1__* frp; } ;
struct TYPE_10__ {char* name; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EX_PRIVATE ;
typedef  int /*<<< orphan*/  EXCMD ;
typedef  int CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_SPACE_RETW (TYPE_2__*,int*,size_t,size_t) ; 
 int /*<<< orphan*/  CHAR2INT (TYPE_2__*,char*,size_t,int*,size_t) ; 
 TYPE_3__* EXP (TYPE_2__*) ; 
 int /*<<< orphan*/  E_MODIFY ; 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMCPY (int*,int*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 size_t STRLEN (int*) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
argv_fexp(SCR *sp, EXCMD *excp, CHAR_T *cmd, size_t cmdlen, CHAR_T *p, size_t *lenp, CHAR_T **bpp, size_t *blenp, int is_bang)
{
	EX_PRIVATE *exp;
	char *t;
	size_t blen, len, off, tlen;
	CHAR_T *bp;
	CHAR_T *wp;
	size_t wlen;

	/* Replace file name characters. */
	for (bp = *bpp, blen = *blenp, len = *lenp; cmdlen > 0; --cmdlen, ++cmd)
		switch (*cmd) {
		case '!':
			if (!is_bang)
				goto ins_ch;
			exp = EXP(sp);
			if (exp->lastbcomm == NULL) {
				msgq(sp, M_ERR,
				    "115|No previous command to replace \"!\"");
				return (1);
			}
			len += tlen = STRLEN(exp->lastbcomm);
			off = p - bp;
			ADD_SPACE_RETW(sp, bp, blen, len);
			p = bp + off;
			MEMCPY(p, exp->lastbcomm, tlen);
			p += tlen;
			F_SET(excp, E_MODIFY);
			break;
		case '%':
			if ((t = sp->frp->name) == NULL) {
				msgq(sp, M_ERR,
				    "116|No filename to substitute for %%");
				return (1);
			}
			tlen = strlen(t);
			len += tlen;
			off = p - bp;
			ADD_SPACE_RETW(sp, bp, blen, len);
			p = bp + off;
			CHAR2INT(sp, t, tlen, wp, wlen);
			MEMCPY(p, wp, wlen);
			p += wlen;
			F_SET(excp, E_MODIFY);
			break;
		case '#':
			if ((t = sp->alt_name) == NULL) {
				msgq(sp, M_ERR,
				    "117|No filename to substitute for #");
				return (1);
			}
			len += tlen = strlen(t);
			off = p - bp;
			ADD_SPACE_RETW(sp, bp, blen, len);
			p = bp + off;
			CHAR2INT(sp, t, tlen, wp, wlen);
			MEMCPY(p, wp, wlen);
			p += wlen;
			F_SET(excp, E_MODIFY);
			break;
		case '\\':
			/*
			 * QUOTING NOTE:
			 *
			 * Strip any backslashes that protected the file
			 * expansion characters.
			 */
			if (cmdlen > 1 &&
			    (cmd[1] == '%' || cmd[1] == '#' || cmd[1] == '!')) {
				++cmd;
				--cmdlen;
			}
			/* FALLTHROUGH */
		default:
ins_ch:			++len;
			off = p - bp;
			ADD_SPACE_RETW(sp, bp, blen, len);
			p = bp + off;
			*p++ = *cmd;
		}

	/* Nul termination. */
	++len;
	off = p - bp;
	ADD_SPACE_RETW(sp, bp, blen, len);
	p = bp + off;
	*p = '\0';

	/* Return the new string length, buffer, buffer length. */
	*lenp = len - 1;
	*bpp = bp;
	*blenp = blen;
	return (0);
}