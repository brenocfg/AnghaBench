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
struct Hist {int /*<<< orphan*/  Hlex; int /*<<< orphan*/  histline; int /*<<< orphan*/  Hnum; } ;
typedef  struct Hist* ptr_t ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  HistLit ; 
 int MB_LEN_MAX ; 
 int Strlen (char*) ; 
 int /*<<< orphan*/  one_wctomb (char*,char) ; 
 char* sprlex (int /*<<< orphan*/ *) ; 
 char* xasprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (int) ; 

char *
fmthist(int fmt, ptr_t ptr)
{
    struct Hist *hp = ptr;
    char *buf;

    switch (fmt) {
    case 'h':
	return xasprintf("%6d", hp->Hnum);
    case 'R':
	if (HistLit && hp->histline)
	    return xasprintf("%S", hp->histline);
	else {
	    Char *istr, *ip;
	    char *p;

	    istr = sprlex(&hp->Hlex);
	    buf = xmalloc(Strlen(istr) * MB_LEN_MAX + 1);

	    for (p = buf, ip = istr; *ip != '\0'; ip++)
		p += one_wctomb(p, *ip);

	    *p = '\0';
	    xfree(istr);
	    return buf;
	}
    default:
	buf = xmalloc(1);
	buf[0] = '\0';
	return buf;
    }
}