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
typedef  int off_t ;

/* Variables and functions */
 int column ; 
 int /*<<< orphan*/  peekbyte (int,char) ; 
 int /*<<< orphan*/  queuelen ; 
 int /*<<< orphan*/  savebyte (char) ; 

__attribute__((used)) static void
savewhite(char c, bool leading)
{
	off_t ncolumn;

	switch (c) {
	case '\n':
		if (leading) {
			/* Remove empty lines before input. */
			queuelen = 0;
			column = 0;
		} else {
			/* Remove trailing whitespace. */
			while (peekbyte(1, ' ') || peekbyte(1, '\t'))
				queuelen--;
			/* Remove redundant empty lines. */
			if (peekbyte(2, '\n') && peekbyte(1, '\n'))
				return;
			savebyte('\n');
		}
		break;
	case ' ':
		savebyte(' ');
		break;
	case '\t':
		/* Convert preceding spaces to tabs. */
		ncolumn = (column / 8 + 1) * 8;
		while (peekbyte(1, ' ')) {
			queuelen--;
			column--;
		}
		while (column < ncolumn)
			savebyte('\t');
		break;
	}
}