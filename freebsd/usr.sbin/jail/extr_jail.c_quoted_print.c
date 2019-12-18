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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static void
quoted_print(FILE *fp, char *str)
{
	int c, qc;
	char *p = str;

	qc = !*p ? '"'
	    : strchr(p, '\'') ? '"'
	    : strchr(p, '"') ? '\''
	    : strchr(p, ' ') || strchr(p, '\t') ? '"'
	    : 0;
	if (qc)
		putc(qc, fp);
	while ((c = *p++)) {
		if (c == '\\' || c == qc)
			putc('\\', fp);
		putc(c, fp);
	}
	if (qc)
		putc(qc, fp);
}