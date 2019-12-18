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
struct TYPE_2__ {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int /*<<< orphan*/  REGEXPR ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTAX (char*,char*) ; 
 int /*<<< orphan*/  adjbuf (char**,int*,int,int,char**,char*) ; 
 void* input () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  tostring (char*) ; 
 int /*<<< orphan*/  unput (char) ; 
 TYPE_1__ yylval ; 

int regexpr(void)
{
	int c;
	static char *buf = NULL;
	static int bufsz = 500;
	char *bp;

	if (buf == NULL && (buf = (char *) malloc(bufsz)) == NULL)
		FATAL("out of space for rex expr");
	bp = buf;
	for ( ; (c = input()) != '/' && c != 0; ) {
		if (!adjbuf(&buf, &bufsz, bp-buf+3, 500, &bp, "regexpr"))
			FATAL("out of space for reg expr %.10s...", buf);
		if (c == '\n') {
			*bp = '\0';
			SYNTAX( "newline in regular expression %.10s...", buf ); 
			unput('\n');
			break;
		} else if (c == '\\') {
			*bp++ = '\\'; 
			*bp++ = input();
		} else {
			*bp++ = c;
		}
	}
	*bp = 0;
	if (c == 0)
		SYNTAX("non-terminated regular expression %.10s...", buf);
	yylval.s = tostring(buf);
	unput('/');
	RET(REGEXPR);
}