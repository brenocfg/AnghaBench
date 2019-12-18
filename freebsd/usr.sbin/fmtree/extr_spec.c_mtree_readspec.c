#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ginfo ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {scalar_t__ type; int flags; struct TYPE_7__* next; struct TYPE_7__* prev; struct TYPE_7__* parent; struct TYPE_7__* child; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ NODE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ F_DIR ; 
 int F_DONE ; 
 int F_MAGIC ; 
 int /*<<< orphan*/  MAGIC ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_1__* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ isspace (char) ; 
 int lineno ; 
 int /*<<< orphan*/  set (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strpbrk (char*,int /*<<< orphan*/ ) ; 
 char* strtok (char*,char*) ; 
 int strunvis (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unset (int /*<<< orphan*/ *,TYPE_1__*) ; 

NODE *
mtree_readspec(FILE *fi)
{
	NODE *centry, *last;
	char *p;
	NODE ginfo, *root;
	int c_cur, c_next;
	char buf[2048];

	centry = last = root = NULL;
	bzero(&ginfo, sizeof(ginfo));
	c_cur = c_next = 0;
	for (lineno = 1; fgets(buf, sizeof(buf), fi);
	    ++lineno, c_cur = c_next, c_next = 0) {
		/* Skip empty lines. */
		if (buf[0] == '\n')
			continue;

		/* Find end of line. */
		if ((p = strchr(buf, '\n')) == NULL)
			errx(1, "line %d too long", lineno);

		/* See if next line is continuation line. */
		if (p[-1] == '\\') {
			--p;
			c_next = 1;
		}

		/* Null-terminate the line. */
		*p = '\0';

		/* Skip leading whitespace. */
		for (p = buf; *p && isspace(*p); ++p);

		/* If nothing but whitespace or comment char, continue. */
		if (!*p || *p == '#')
			continue;

#ifdef DEBUG
		(void)fprintf(stderr, "line %d: {%s}\n", lineno, p);
#endif
		if (c_cur) {
			set(p, centry);
			continue;
		}

		/* Grab file name, "$", "set", or "unset". */
		if ((p = strtok(p, "\n\t ")) == NULL)
			errx(1, "line %d: missing field", lineno);

		if (p[0] == '/')
			switch(p[1]) {
			case 's':
				if (strcmp(p + 1, "set"))
					break;
				set(NULL, &ginfo);
				continue;
			case 'u':
				if (strcmp(p + 1, "unset"))
					break;
				unset(NULL, &ginfo);
				continue;
			}

		if (strchr(p, '/'))
			errx(1, "line %d: slash character in file name",
			lineno);

		if (!strcmp(p, "..")) {
			/* Don't go up, if haven't gone down. */
			if (!root)
				goto noparent;
			if (last->type != F_DIR || last->flags & F_DONE) {
				if (last == root)
					goto noparent;
				last = last->parent;
			}
			last->flags |= F_DONE;
			continue;

noparent:		errx(1, "line %d: no parent node", lineno);
		}

		if ((centry = calloc(1, sizeof(NODE) + strlen(p))) == NULL)
			errx(1, "calloc");
		*centry = ginfo;
#define	MAGIC	"?*["
		if (strpbrk(p, MAGIC))
			centry->flags |= F_MAGIC;
		if (strunvis(centry->name, p) == -1)
			errx(1, "filename %s is ill-encoded", p);
		set(NULL, centry);

		if (!root) {
			last = root = centry;
			root->parent = root;
		} else if (last->type == F_DIR && !(last->flags & F_DONE)) {
			centry->parent = last;
			last = last->child = centry;
		} else {
			centry->parent = last->parent;
			centry->prev = last;
			last = last->next = centry;
		}
	}
	return (root);
}