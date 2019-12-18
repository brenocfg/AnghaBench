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
struct command {unsigned int lineno; char* str; int /*<<< orphan*/  type; struct command* next; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EXPECT ; 
 int /*<<< orphan*/  CMD_PASSWORD ; 
 int /*<<< orphan*/  CMD_SEND ; 
 struct command* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* iscmd (char*,char*) ; 
 struct command** next ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static void
parse_configuration(const char *fn)
{
    struct command *c;
    char s[1024];
    char *str;
    unsigned int lineno = 0;
    FILE *cmd;

    cmd = fopen(fn, "r");
    if (cmd == NULL)
	err(1, "open: %s", fn);

    while (fgets(s, sizeof(s),  cmd) != NULL) {

	s[strcspn(s, "#\n")] = '\0';
	lineno++;

	c = calloc(1, sizeof(*c));
	if (c == NULL)
	    errx(1, "malloc");

	c->lineno = lineno;
	(*next) = c;
	next = &(c->next);

	if ((str = iscmd(s, "expect ")) != NULL) {
	    c->type = CMD_EXPECT;
	    c->str = str;
	} else if ((str = iscmd(s, "send ")) != NULL) {
	    c->type = CMD_SEND;
	    c->str = str;
	} else if ((str = iscmd(s, "password ")) != NULL) {
	    c->type = CMD_PASSWORD;
	    c->str = str;
	} else
	    errx(1, "Invalid command on line %d: %s", lineno, s);
    }

    fclose(cmd);
}