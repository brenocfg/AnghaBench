#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int DIGIT ; 
 int HEX ; 
 size_t* cp ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int* map ; 
 unsigned int ones (int) ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 TYPE_1__* widechar ; 

__attribute__((used)) static int backslash(int q) {
	unsigned int c;

	switch (*cp++) {
	case 'a': return 7;
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';
	case '\'': case '"': case '\\': case '\?': break;
	case 'x': {
		int overflow = 0;
		if ((map[*cp]&(DIGIT|HEX)) == 0) {
			if (*cp < ' ' || *cp == 0177)
				error("ill-formed hexadecimal escape sequence\n");
			else
				error("ill-formed hexadecimal escape sequence `\\x%c'\n", *cp);
			if (*cp != q)
				cp++;
			return 0;
		}
		for (c = 0; map[*cp]&(DIGIT|HEX); cp++) {
			if (c >> (8*widechar->size - 4))
				overflow = 1;
			if (map[*cp]&DIGIT)
				c = (c<<4) + *cp - '0';
			else
				c = (c<<4) + (*cp&~040) - 'A' + 10;
		}
		if (overflow)
			warning("overflow in hexadecimal escape sequence\n");
		return c&ones(8*widechar->size);
		}
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
		c = *(cp-1) - '0';
		if (*cp >= '0' && *cp <= '7') {
			c = (c<<3) + *cp++ - '0';
			if (*cp >= '0' && *cp <= '7')
				c = (c<<3) + *cp++ - '0';
		}
		return c;
	default:
		if (cp[-1] < ' ' || cp[-1] >= 0177)
			warning("unrecognized character escape sequence\n");
		else
			warning("unrecognized character escape sequence `\\%c'\n", cp[-1]);
	}
	return cp[-1];
}