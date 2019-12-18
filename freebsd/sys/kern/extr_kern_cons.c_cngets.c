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

/* Variables and functions */
#define  GETS_ECHOPASS 129 
#define  GETS_NOECHO 128 
 int cngetc () ; 
 int /*<<< orphan*/  cngrab () ; 
 int /*<<< orphan*/  cnputc (int) ; 
 int /*<<< orphan*/  cnputs (char*) ; 
 int /*<<< orphan*/  cnungrab () ; 

void
cngets(char *cp, size_t size, int visible)
{
	char *lp, *end;
	int c;

	cngrab();

	lp = cp;
	end = cp + size - 1;
	for (;;) {
		c = cngetc() & 0177;
		switch (c) {
		case '\n':
		case '\r':
			cnputc(c);
			*lp = '\0';
			cnungrab();
			return;
		case '\b':
		case '\177':
			if (lp > cp) {
				if (visible)
					cnputs("\b \b");
				lp--;
			}
			continue;
		case '\0':
			continue;
		default:
			if (lp < end) {
				switch (visible) {
				case GETS_NOECHO:
					break;
				case GETS_ECHOPASS:
					cnputc('*');
					break;
				default:
					cnputc(c);
					break;
				}
				*lp++ = c;
			}
		}
	}
}