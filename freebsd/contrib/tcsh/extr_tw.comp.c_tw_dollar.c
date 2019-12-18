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
struct Strbuf {int dummy; } ;
typedef  char const Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_COMPMIS ; 
 scalar_t__ Isdigit (char const) ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,char const*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 char* Strbuf_finish (struct Strbuf*) ; 
 int /*<<< orphan*/  short2str (char const*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char const*) ; 

__attribute__((used)) static const Char *
tw_dollar(const Char *str, Char **wl, size_t nwl, Char **result, Char sep,
	  const char *msg)
{
    struct Strbuf buf = Strbuf_INIT;
    Char *res;
    const Char *sp;

    for (sp = str; *sp && *sp != sep;)
	if (sp[0] == '$' && sp[1] == ':' && Isdigit(sp[sp[2] == '-' ? 3 : 2])) {
	    int num, neg = 0;
	    sp += 2;
	    if (*sp == '-') {
		neg = 1;
		sp++;
	    }
	    for (num = *sp++ - '0'; Isdigit(*sp); num += 10 * num + *sp++ - '0')
		continue;
	    if (neg)
		num = nwl - num - 1;
	    if (num >= 0 && (size_t)num < nwl)
		Strbuf_append(&buf, wl[num]);
	}
	else
	    Strbuf_append1(&buf, *sp++);

    res = Strbuf_finish(&buf);

    if (*sp++ == sep) {
	*result = res;
	return sp;
    }

    xfree(res);
    /* Truncates data if WIDE_STRINGS */
    stderror(ERR_COMPMIS, (int)sep, msg, short2str(str));
    return --sp;
}