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
typedef  int uschar ;

/* Variables and functions */
 int EOF ; 
 int* ebuf ; 
 int* ep ; 
 int pgetc () ; 
 scalar_t__* yysbuf ; 
 scalar_t__* yysptr ; 

int input(void)	/* get next lexical input character */
{
	int c;
	extern char *lexprog;

	if (yysptr > yysbuf)
		c = (uschar)*--yysptr;
	else if (lexprog != NULL) {	/* awk '...' */
		if ((c = (uschar)*lexprog) != 0)
			lexprog++;
	} else				/* awk -f ... */
		c = pgetc();
	if (c == EOF)
		c = 0;
	if (ep >= ebuf + sizeof ebuf)
		ep = ebuf;
	*ep = c;
	if (c != 0) {
		ep++;
	}
	return (c);
}