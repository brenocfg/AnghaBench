#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Strbuf {size_t len; } ;
struct TYPE_4__ {int const* s; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int* s; } ;
typedef  int Char ;

/* Variables and functions */
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int const*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int const) ; 
 int /*<<< orphan*/  Strbuf_appendn (struct Strbuf*,int*,int) ; 
 int* Strbuf_finish (struct Strbuf*) ; 
 int* Strsave (int*) ; 
 int* domod (int*,int) ; 
 TYPE_2__ lhsb ; 
 int /*<<< orphan*/  matchs (int const*,int const*) ; 
 TYPE_1__ rhsb ; 

__attribute__((used)) static Char *
subword(Char *cp, Char type, int *adid, size_t *start_pos)
{
    Char *wp;
    const Char *mp, *np;

    switch (type) {

    case 'r':
    case 'e':
    case 'h':
    case 't':
    case 'q':
    case 'x':
    case 'u':
    case 'l':
	wp = domod(cp, type);
	if (wp == 0) {
	    *adid = 0;
	    return (Strsave(cp));
	}
	*adid = 1;
	return (wp);

    default:
	for (mp = cp + *start_pos; *mp; mp++) {
	    if (matchs(mp, lhsb.s)) {
		struct Strbuf wbuf = Strbuf_INIT;

		Strbuf_appendn(&wbuf, cp, mp - cp);
		for (np = rhsb.s; *np; np++)
		    switch (*np) {

		    case '\\':
			if (np[1] == '&')
			    np++;
			/* fall into ... */

		    default:
			Strbuf_append1(&wbuf, *np);
			continue;

		    case '&':
			Strbuf_append(&wbuf, lhsb.s);
			continue;
		    }
		*start_pos = wbuf.len;
		Strbuf_append(&wbuf, mp + lhsb.len);
		*adid = 1;
		return Strbuf_finish(&wbuf);
	    }
	}
	*adid = 0;
	return (Strsave(cp));
    }
}