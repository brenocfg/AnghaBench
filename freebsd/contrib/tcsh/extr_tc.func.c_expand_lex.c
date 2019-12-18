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
struct wordent {char* word; struct wordent* next; struct wordent* prev; } ;
struct Strbuf {scalar_t__ len; } ;
typedef  char Char ;

/* Variables and functions */
 char HIST ; 
 char INVALID_BYTE ; 
 char QUOTE ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char) ; 
 char* Strbuf_finish (struct Strbuf*) ; 
 char TRIM ; 

Char   *
expand_lex(const struct wordent *sp0, int from, int to)
{
    struct Strbuf buf = Strbuf_INIT;
    const struct wordent *sp;
    Char *s;
    Char prev_c;
    int i;

    prev_c = '\0';

    if (!sp0 || (sp = sp0->next) == sp0 || sp == (sp0 = sp0->prev))
	return Strbuf_finish(&buf); /* null lex */

    for (i = 0; ; i++) {
	if ((i >= from) && (i <= to)) {	/* if in range */
	    for (s = sp->word; *s; s++) {
		/*
		 * bugfix by Michael Bloom: anything but the current history
		 * character {(PWP) and backslash} seem to be dealt with
		 * elsewhere.
		 */
		if ((*s & QUOTE)
		    && (((*s & TRIM) == HIST && HIST != '\0') ||
			(((*s & TRIM) == '\'') && (prev_c != '\\')) ||
			(((*s & TRIM) == '\"') && (prev_c != '\\')))) {
		    Strbuf_append1(&buf, '\\');
		}
#if INVALID_BYTE != 0
		if ((*s & INVALID_BYTE) != INVALID_BYTE) /* *s < INVALID_BYTE */
		    Strbuf_append1(&buf, *s & TRIM);
		else
		    Strbuf_append1(&buf, *s);
#else
		Strbuf_append1(&buf, *s & TRIM);
#endif
		prev_c = *s;
	    }
	    Strbuf_append1(&buf, ' ');
	}
	sp = sp->next;
	if (sp == sp0)
	    break;
    }
    if (buf.len != 0)
	buf.len--;		/* get rid of trailing space */

    return Strbuf_finish(&buf);
}