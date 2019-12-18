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
typedef  char eChar ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 char DEOF ; 
 int /*<<< orphan*/  DODOL ; 
 char DgetC (int /*<<< orphan*/ ) ; 
 char QUOTE ; 
 int QUOTES ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int _NL ; 
 int _QB ; 
 int _QF ; 
 int _SP ; 
 scalar_t__ cmap (char,int) ; 
 int /*<<< orphan*/  unDgetC (char) ; 
 int /*<<< orphan*/  unDredc (char) ; 

__attribute__((used)) static int
Dpack(struct Strbuf *wbuf)
{
    eChar c;

    for (;;) {
	c = DgetC(DODOL);
	if (c == '\\') {
	    c = DgetC(0);
	    if (c == DEOF) {
		unDredc(c);
		return 1;
	    }
	    if (c == '\n')
		c = ' ';
	    else
		c |= QUOTE;
	}
	if (c == DEOF) {
	    unDredc(c);
	    return 1;
	}
	if (cmap(c, _SP | _NL | _QF | _QB)) {	/* sp \t\n'"` */
	    unDgetC(c);
	    if (cmap(c, QUOTES))
		return 0;
	    return 1;
	}
	Strbuf_append1(wbuf, (Char) c);
    }
}