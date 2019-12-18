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
struct TYPE_2__ {int i; void* cp; } ;

/* Variables and functions */
 int ADDEQ ; 
 int AND ; 
 int APPEND ; 
 int ASGNOP ; 
 int ASSIGN ; 
 int BOR ; 
 int CON ; 
 int DECR ; 
 int EQ ; 
 int /*<<< orphan*/  FATAL (char*) ; 
 int GE ; 
 int GT ; 
 int INCR ; 
 int INDIRECT ; 
 int IVAR ; 
 int LE ; 
 int LT ; 
 int MATCH ; 
 int MATCHOP ; 
 int MODEQ ; 
 int MULTEQ ; 
 int NE ; 
 int NL ; 
 int NOT ; 
 int NOTMATCH ; 
 int NUM ; 
 int NUMBER ; 
 void* POWEQ ; 
 int POWER ; 
 int /*<<< orphan*/  RET (int) ; 
 int STR ; 
 int SUBEQ ; 
 int /*<<< orphan*/  SYNTAX (char*) ; 
 double atof (char*) ; 
 int /*<<< orphan*/  bracecnt ; 
 int /*<<< orphan*/  brackcnt ; 
 int gettok (char**,int*) ; 
 int /*<<< orphan*/  infunc ; 
 int input () ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  isarg (char*) ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  lineno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  parencnt ; 
 char peek () ; 
 scalar_t__ reg ; 
 int regexpr () ; 
 int sc ; 
 void* setsymtab (char*,char*,double,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int string () ; 
 int /*<<< orphan*/  symtab ; 
 char* tostring (char*) ; 
 int /*<<< orphan*/  unput (int) ; 
 int /*<<< orphan*/  unputstr (char*) ; 
 int word (char*) ; 
 TYPE_1__ yylval ; 

int yylex(void)
{
	int c;
	static char *buf = NULL;
	static int bufsize = 5; /* BUG: setting this small causes core dump! */

	if (buf == NULL && (buf = (char *) malloc(bufsize)) == NULL)
		FATAL( "out of space in yylex" );
	if (sc) {
		sc = 0;
		RET('}');
	}
	if (reg) {
		reg = 0;
		return regexpr();
	}
	for (;;) {
		c = gettok(&buf, &bufsize);
		if (c == 0)
			return 0;
		if (isalpha(c) || c == '_')
			return word(buf);
		if (isdigit(c)) {
			yylval.cp = setsymtab(buf, tostring(buf), atof(buf), CON|NUM, symtab);
			/* should this also have STR set? */
			RET(NUMBER);
		}
	
		yylval.i = c;
		switch (c) {
		case '\n':	/* {EOL} */
			lineno++;
			RET(NL);
		case '\r':	/* assume \n is coming */
		case ' ':	/* {WS}+ */
		case '\t':
			break;
		case '#':	/* #.* strip comments */
			while ((c = input()) != '\n' && c != 0)
				;
			unput(c);
			break;
		case ';':
			RET(';');
		case '\\':
			if (peek() == '\n') {
				input();
				lineno++;
			} else if (peek() == '\r') {
				input(); input();	/* \n */
				lineno++;
			} else {
				RET(c);
			}
			break;
		case '&':
			if (peek() == '&') {
				input(); RET(AND);
			} else 
				RET('&');
		case '|':
			if (peek() == '|') {
				input(); RET(BOR);
			} else
				RET('|');
		case '!':
			if (peek() == '=') {
				input(); yylval.i = NE; RET(NE);
			} else if (peek() == '~') {
				input(); yylval.i = NOTMATCH; RET(MATCHOP);
			} else
				RET(NOT);
		case '~':
			yylval.i = MATCH;
			RET(MATCHOP);
		case '<':
			if (peek() == '=') {
				input(); yylval.i = LE; RET(LE);
			} else {
				yylval.i = LT; RET(LT);
			}
		case '=':
			if (peek() == '=') {
				input(); yylval.i = EQ; RET(EQ);
			} else {
				yylval.i = ASSIGN; RET(ASGNOP);
			}
		case '>':
			if (peek() == '=') {
				input(); yylval.i = GE; RET(GE);
			} else if (peek() == '>') {
				input(); yylval.i = APPEND; RET(APPEND);
			} else {
				yylval.i = GT; RET(GT);
			}
		case '+':
			if (peek() == '+') {
				input(); yylval.i = INCR; RET(INCR);
			} else if (peek() == '=') {
				input(); yylval.i = ADDEQ; RET(ASGNOP);
			} else
				RET('+');
		case '-':
			if (peek() == '-') {
				input(); yylval.i = DECR; RET(DECR);
			} else if (peek() == '=') {
				input(); yylval.i = SUBEQ; RET(ASGNOP);
			} else
				RET('-');
		case '*':
			if (peek() == '=') {	/* *= */
				input(); yylval.i = MULTEQ; RET(ASGNOP);
			} else if (peek() == '*') {	/* ** or **= */
				input();	/* eat 2nd * */
				if (peek() == '=') {
					input(); yylval.i = POWEQ; RET(ASGNOP);
				} else {
					RET(POWER);
				}
			} else
				RET('*');
		case '/':
			RET('/');
		case '%':
			if (peek() == '=') {
				input(); yylval.i = MODEQ; RET(ASGNOP);
			} else
				RET('%');
		case '^':
			if (peek() == '=') {
				input(); yylval.i = POWEQ; RET(ASGNOP);
			} else
				RET(POWER);

		case '$':
			/* BUG: awkward, if not wrong */
			c = gettok(&buf, &bufsize);
			if (isalpha(c)) {
				if (strcmp(buf, "NF") == 0) {	/* very special */
					unputstr("(NF)");
					RET(INDIRECT);
				}
				c = peek();
				if (c == '(' || c == '[' || (infunc && isarg(buf) >= 0)) {
					unputstr(buf);
					RET(INDIRECT);
				}
				yylval.cp = setsymtab(buf, "", 0.0, STR|NUM, symtab);
				RET(IVAR);
			} else if (c == 0) {	/*  */
				SYNTAX( "unexpected end of input after $" );
				RET(';');
			} else {
				unputstr(buf);
				RET(INDIRECT);
			}
	
		case '}':
			if (--bracecnt < 0)
				SYNTAX( "extra }" );
			sc = 1;
			RET(';');
		case ']':
			if (--brackcnt < 0)
				SYNTAX( "extra ]" );
			RET(']');
		case ')':
			if (--parencnt < 0)
				SYNTAX( "extra )" );
			RET(')');
		case '{':
			bracecnt++;
			RET('{');
		case '[':
			brackcnt++;
			RET('[');
		case '(':
			parencnt++;
			RET('(');
	
		case '"':
			return string();	/* BUG: should be like tran.c ? */
	
		default:
			RET(c);
		}
	}
}