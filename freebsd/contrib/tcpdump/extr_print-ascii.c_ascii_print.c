#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  char u_char ;
struct TYPE_4__ {char const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_ISGRAPH (char) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 

void
ascii_print(netdissect_options *ndo,
            const u_char *cp, u_int length)
{
	u_int caplength;
	register u_char s;

	caplength = (ndo->ndo_snapend >= cp) ? ndo->ndo_snapend - cp : 0;
	if (length > caplength)
		length = caplength;
	ND_PRINT((ndo, "\n"));
	while (length > 0) {
		s = *cp++;
		length--;
		if (s == '\r') {
			/*
			 * Don't print CRs at the end of the line; they
			 * don't belong at the ends of lines on UN*X,
			 * and the standard I/O library will give us one
			 * on Windows so we don't need to print one
			 * ourselves.
			 *
			 * In the middle of a line, just print a '.'.
			 */
			if (length > 1 && *cp != '\n')
				ND_PRINT((ndo, "."));
		} else {
			if (!ND_ISGRAPH(s) &&
			    (s != '\t' && s != ' ' && s != '\n'))
				ND_PRINT((ndo, "."));
			else
				ND_PRINT((ndo, "%c", s));
		}
	}
}