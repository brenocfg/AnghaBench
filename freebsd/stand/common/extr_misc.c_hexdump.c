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
typedef  int uint8_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  pager_close () ; 
 int /*<<< orphan*/  pager_open () ; 

void
hexdump(caddr_t region, size_t len)
{
    caddr_t	line;
    int		x, c;
    char	lbuf[80];
#define emit(fmt, args...)	{sprintf(lbuf, fmt , ## args); pager_output(lbuf);}

    pager_open();
    for (line = region; line < (region + len); line += 16) {
	emit("%08lx  ", (long) line);
	
	for (x = 0; x < 16; x++) {
	    if ((line + x) < (region + len)) {
		emit("%02x ", *(uint8_t *)(line + x));
	    } else {
		emit("-- ");
	    }
	    if (x == 7)
		emit(" ");
	}
	emit(" |");
	for (x = 0; x < 16; x++) {
	    if ((line + x) < (region + len)) {
		c = *(uint8_t *)(line + x);
		if ((c < ' ') || (c > '~'))	/* !isprint(c) */
		    c = '.';
		emit("%c", c);
	    } else {
		emit(" ");
	    }
	}
	emit("|\n");
    }
    pager_close();
}