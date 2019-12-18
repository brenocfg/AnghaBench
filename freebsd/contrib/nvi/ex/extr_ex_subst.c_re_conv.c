#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t repl_len; int /*<<< orphan*/  repl; } ;
typedef  TYPE_1__ SCR ;
typedef  int CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SPACE_RETW (TYPE_1__*,int*,size_t,size_t) ; 
 int /*<<< orphan*/  MEMCPY (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  O_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_MAGIC ; 
 int /*<<< orphan*/  RE_WSTART ; 
 size_t RE_WSTART_LEN ; 
 int /*<<< orphan*/  RE_WSTOP ; 
 size_t RE_WSTOP_LEN ; 

__attribute__((used)) static int
re_conv(SCR *sp, CHAR_T **ptrnp, size_t *plenp, int *replacedp)
{
	size_t blen, len, needlen;
	int magic;
	CHAR_T *bp, *p, *t;

	/*
	 * First pass through, we figure out how much space we'll need.
	 * We do it in two passes, on the grounds that most of the time
	 * the user is doing a search and won't have magic characters.
	 * That way we can skip most of the memory allocation and copies.
	 */
	magic = 0;
	for (p = *ptrnp, len = *plenp, needlen = 0; len > 0; ++p, --len)
		switch (*p) {
		case '\\':
			if (len > 1) {
				--len;
				switch (*++p) {
				case '<':
					magic = 1;
					needlen += RE_WSTART_LEN + 1;
					break;
				case '>':
					magic = 1;
					needlen += RE_WSTOP_LEN + 1;
					break;
				case '~':
					if (!O_ISSET(sp, O_MAGIC)) {
						magic = 1;
						needlen += sp->repl_len;
					}
					break;
				case '.':
				case '[':
				case '*':
					if (!O_ISSET(sp, O_MAGIC)) {
						magic = 1;
						needlen += 1;
					}
					break;
				default:
					needlen += 2;
				}
			} else
				needlen += 1;
			break;
		case '~':
			if (O_ISSET(sp, O_MAGIC)) {
				magic = 1;
				needlen += sp->repl_len;
			}
			break;
		case '.':
		case '[':
		case '*':
			if (!O_ISSET(sp, O_MAGIC)) {
				magic = 1;
				needlen += 2;
			}
			break;
		default:
			needlen += 1;
			break;
		}

	if (!magic) {
		*replacedp = 0;
		return (0);
	}

	/* Get enough memory to hold the final pattern. */
	*replacedp = 1;
	GET_SPACE_RETW(sp, bp, blen, needlen);

	for (p = *ptrnp, len = *plenp, t = bp; len > 0; ++p, --len)
		switch (*p) {
		case '\\':
			if (len > 1) {
				--len;
				switch (*++p) {
				case '<':
					MEMCPY(t,
					    RE_WSTART, RE_WSTART_LEN);
					t += RE_WSTART_LEN;
					break;
				case '>':
					MEMCPY(t,
					    RE_WSTOP, RE_WSTOP_LEN);
					t += RE_WSTOP_LEN;
					break;
				case '~':
					if (O_ISSET(sp, O_MAGIC))
						*t++ = '~';
					else {
						MEMCPY(t,
						    sp->repl, sp->repl_len);
						t += sp->repl_len;
					}
					break;
				case '.':
				case '[':
				case '*':
					if (O_ISSET(sp, O_MAGIC))
						*t++ = '\\';
					*t++ = *p;
					break;
				default:
					*t++ = '\\';
					*t++ = *p;
				}
			} else
				*t++ = '\\';
			break;
		case '~':
			if (O_ISSET(sp, O_MAGIC)) {
				MEMCPY(t, sp->repl, sp->repl_len);
				t += sp->repl_len;
			} else
				*t++ = '~';
			break;
		case '.':
		case '[':
		case '*':
			if (!O_ISSET(sp, O_MAGIC))
				*t++ = '\\';
			*t++ = *p;
			break;
		default:
			*t++ = *p;
			break;
		}

	*ptrnp = bp;
	*plenp = t - bp;
	return (0);
}