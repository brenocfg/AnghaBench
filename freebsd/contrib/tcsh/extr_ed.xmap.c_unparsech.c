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
typedef  int Char ;

/* Variables and functions */
 int CTL_ESC (char) ; 
 scalar_t__ Iscntrl (int) ; 
 scalar_t__ Isprint (int) ; 
 int /*<<< orphan*/  Isspace (int) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int) ; 
 int* _toascii ; 
 int* _toebcdic ; 

__attribute__((used)) static void
unparsech(struct Strbuf *buf, Char ch)
{
    if (ch == 0) {
	Strbuf_append1(buf, '^');
	Strbuf_append1(buf, '@');
    }
    else if (Iscntrl(ch)) {
	Strbuf_append1(buf, '^');
	if (ch == CTL_ESC('\177'))
	    Strbuf_append1(buf, '?');
	else
#ifdef IS_ASCII
	    Strbuf_append1(buf, ch | 0100);
#else
	    Strbuf_append1(buf, _toebcdic[_toascii[ch]|0100]);
#endif
    }
    else if (ch == '^') {
	Strbuf_append1(buf, '\\');
	Strbuf_append1(buf, '^');
    } else if (ch == '\\') {
	Strbuf_append1(buf, '\\');
	Strbuf_append1(buf, '\\');
    } else if (ch == ' ' || (Isprint(ch) && !Isspace(ch))) {
	Strbuf_append1(buf, ch);
    }
    else {
	Strbuf_append1(buf, '\\');
	Strbuf_append1(buf, ((ch >> 6) & 7) + '0');
	Strbuf_append1(buf, ((ch >> 3) & 7) + '0');
	Strbuf_append1(buf, (ch & 7) + '0');
    }
}