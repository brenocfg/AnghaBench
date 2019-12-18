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
typedef  void* recno_t ;
struct TYPE_5__ {void* lno; } ;
typedef  TYPE_1__ SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCR_TOP ; 
 int /*<<< orphan*/  db_get (TYPE_1__*,void*,int /*<<< orphan*/ ,char**,size_t*) ; 

__attribute__((used)) static void
file_comment(SCR *sp)
{
	recno_t lno;
	size_t len;
	CHAR_T *p;

	for (lno = 1; !db_get(sp, lno, 0, &p, &len) && len == 0; ++lno);
	if (p == NULL)
		return;
	if (p[0] == '#') {
		F_SET(sp, SC_SCR_TOP);
		while (!db_get(sp, ++lno, 0, &p, &len))
			if (len < 1 || p[0] != '#') {
				sp->lno = lno;
				return;
			}
	} else if (len > 1 && p[0] == '/' && p[1] == '*') {
		F_SET(sp, SC_SCR_TOP);
		do {
			for (; len > 1; --len, ++p)
				if (p[0] == '*' && p[1] == '/') {
					sp->lno = lno;
					return;
				}
		} while (!db_get(sp, ++lno, 0, &p, &len));
	} else if (len > 1 && p[0] == '/' && p[1] == '/') {
		F_SET(sp, SC_SCR_TOP);
		p += 2;
		len -= 2;
		do {
			for (; len > 1; --len, ++p)
				if (p[0] == '/' && p[1] == '/') {
					sp->lno = lno;
					return;
				}
		} while (!db_get(sp, ++lno, 0, &p, &len));
	}
}