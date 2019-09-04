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
struct TYPE_2__ {int n; scalar_t__* string; } ;

/* Variables and functions */
 int CODE ; 
 int EOF ; 
 int ID ; 
 int INT ; 
 int INT_MAX ; 
 int PPERCENT ; 
 int START ; 
 int TEMPLATE ; 
 int TERMINAL ; 
 void* alloc (int) ; 
 int /*<<< orphan*/  assert (char*) ; 
 char* bp ; 
 scalar_t__ code ; 
 int get () ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ isprint (int) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  ppercent ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 int /*<<< orphan*/  yyerror (char*,...) ; 
 TYPE_1__ yylval ; 

int yylex(void) {
	int c;

	if (code) {
		char *p;
		bp += strspn(bp, " \t\f");
		p = strchr(bp, '\n');
		if (p == NULL)
			p = strchr(bp, '\n');
		while (p > bp && isspace(p[-1]))
			p--;
		yylval.string = alloc(p - bp + 1);
		strncpy(yylval.string, bp, p - bp);
		yylval.string[p - bp] = 0;
		bp = p;
		code--;
		return CODE;
	}
	while ((c = get()) != EOF) {
		switch (c) {
		case ' ': case '\f': case '\t':
			continue;
		case '\n':
		case '(': case ')': case ',':
		case ':': case '=':
			return c;
		}
		if (c == '%' && *bp == '%') {
			bp++;
			return ppercent++ ? 0 : PPERCENT;
		} else if (c == '%' && strncmp(bp, "term", 4) == 0
		&& isspace(bp[4])) {
			bp += 4;
			return TERMINAL;
		} else if (c == '%' && strncmp(bp, "start", 5) == 0
		&& isspace(bp[5])) {
			bp += 5;
			return START;
		} else if (c == '"') {
			char *p = strchr(bp, '"');
			if (p == NULL) {
				yyerror("missing \" in assembler template\n");
				p = strchr(bp, '\n');
				if (p == NULL)
					p = strchr(bp, '\0');
			}
			assert(p);
			yylval.string = alloc(p - bp + 1);
			strncpy(yylval.string, bp, p - bp);
			yylval.string[p - bp] = 0;
			bp = *p == '"' ? p + 1 : p;
			code++;
			return TEMPLATE;
		} else if (isdigit(c)) {
			int n = 0;
			do {
				int d = c - '0';
				if (n > (INT_MAX - d)/10)
					yyerror("integer greater than %d\n", INT_MAX);
				else
					n = 10*n + d;
				c = get();
			} while (c != EOF && isdigit(c));
			bp--;
			yylval.n = n;
			return INT;
		} else if (isalpha(c)) {
			char *p = bp - 1;
			while (isalpha(*bp) || isdigit(*bp) || *bp == '_')
				bp++;
			yylval.string = alloc(bp - p + 1);
			strncpy(yylval.string, p, bp - p);
			yylval.string[bp - p] = 0;
			return ID;
		} else if (isprint(c))
			yyerror("invalid character `%c'\n", c);
		else
			yyerror("invalid character `\\%03o'\n", (unsigned char)c);
	}
	return 0;
}