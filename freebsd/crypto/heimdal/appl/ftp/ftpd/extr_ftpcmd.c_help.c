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
struct tab {char* name; int /*<<< orphan*/  help; scalar_t__ implemented; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct tab* lookup (struct tab*,char*) ; 
 int /*<<< orphan*/  lreply (int,char*,char*,...) ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 
 struct tab* sitetab ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strupr (char*) ; 

__attribute__((used)) static void
help(struct tab *ctab, char *s)
{
	struct tab *c;
	int width, NCMDS;
	char *t;
	char buf[1024];

	if (ctab == sitetab)
		t = "SITE ";
	else
		t = "";
	width = 0, NCMDS = 0;
	for (c = ctab; c->name != NULL; c++) {
		int len = strlen(c->name);

		if (len > width)
			width = len;
		NCMDS++;
	}
	width = (width + 8) &~ 7;
	if (s == 0) {
		int i, j, w;
		int columns, lines;

		lreply(214, "The following %scommands are recognized %s.",
		    t, "(* =>'s unimplemented)");
		columns = 76 / width;
		if (columns == 0)
			columns = 1;
		lines = (NCMDS + columns - 1) / columns;
		for (i = 0; i < lines; i++) {
		    strlcpy (buf, "   ", sizeof(buf));
		    for (j = 0; j < columns; j++) {
			c = ctab + j * lines + i;
			snprintf (buf + strlen(buf),
				  sizeof(buf) - strlen(buf),
				  "%s%c",
				  c->name,
				  c->implemented ? ' ' : '*');
			if (c + lines >= &ctab[NCMDS])
			    break;
			w = strlen(c->name) + 1;
			while (w < width) {
			    strlcat (buf,
					     " ",
					     sizeof(buf));
			    w++;
			}
		    }
		    lreply(214, "%s", buf);
		}
		reply(214, "Direct comments to kth-krb-bugs@pdc.kth.se");
		return;
	}
	strupr(s);
	c = lookup(ctab, s);
	if (c == (struct tab *)0) {
		reply(502, "Unknown command %s.", s);
		return;
	}
	if (c->implemented)
		reply(214, "Syntax: %s%s %s", t, c->name, c->help);
	else
		reply(214, "%s%-*s\t%s; unimplemented.", t, width,
		    c->name, c->help);
}