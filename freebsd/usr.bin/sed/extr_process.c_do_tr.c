#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
struct s_tr {char* bytetab; int nmultis; TYPE_1__* multis; } ;
struct TYPE_7__ {int /*<<< orphan*/  back; int /*<<< orphan*/  space; int /*<<< orphan*/  append_newline; scalar_t__ len; } ;
struct TYPE_6__ {size_t fromlen; char* to; int tolen; int /*<<< orphan*/  from; } ;
typedef  TYPE_2__ SPACE ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND ; 
 int MB_CUR_MAX ; 
 TYPE_2__ PS ; 
 TYPE_2__ YS ; 
 int /*<<< orphan*/  cspace (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 char* ps ; 
 int /*<<< orphan*/  psanl ; 
 size_t psl ; 

__attribute__((used)) static void
do_tr(struct s_tr *y)
{
	SPACE tmp;
	char c, *p;
	size_t clen, left;
	int i;

	if (MB_CUR_MAX == 1) {
		/*
		 * Single-byte encoding: perform in-place translation
		 * of the pattern space.
		 */
		for (p = ps; p < &ps[psl]; p++)
			*p = y->bytetab[(u_char)*p];
	} else {
		/*
		 * Multi-byte encoding: perform translation into the
		 * translation space, then swap the translation and
		 * pattern spaces.
		 */
		/* Clean translation space. */
		YS.len = 0;
		for (p = ps, left = psl; left > 0; p += clen, left -= clen) {
			if ((c = y->bytetab[(u_char)*p]) != '\0') {
				cspace(&YS, &c, 1, APPEND);
				clen = 1;
				continue;
			}
			for (i = 0; i < y->nmultis; i++)
				if (left >= y->multis[i].fromlen &&
				    memcmp(p, y->multis[i].from,
				    y->multis[i].fromlen) == 0)
					break;
			if (i < y->nmultis) {
				cspace(&YS, y->multis[i].to,
				    y->multis[i].tolen, APPEND);
				clen = y->multis[i].fromlen;
			} else {
				cspace(&YS, p, 1, APPEND);
				clen = 1;
			}
		}
		/* Swap the translation space and the pattern space. */
		tmp = PS;
		PS = YS;
		psanl = tmp.append_newline;
		YS = tmp;
		YS.space = YS.back;
	}
}