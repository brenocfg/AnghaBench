#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  ginfo ;
struct TYPE_11__ {scalar_t__ type; int flags; char* name; struct TYPE_11__* parent; scalar_t__ lineno; struct TYPE_11__* child; struct TYPE_11__* next; } ;
typedef  TYPE_1__ NODE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FPARSELN_UNESCCOMM ; 
 scalar_t__ F_DIR ; 
 int F_DONE ; 
 int F_MAGIC ; 
 int /*<<< orphan*/  MAGIC ; 
 int /*<<< orphan*/  addchild (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 char* fparseln (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtree_err (char*,...) ; 
 scalar_t__ mtree_lineno ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  replacenode (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  set (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strpbrk (char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int strunvis (char*,char*) ; 
 int /*<<< orphan*/  unset (char*,TYPE_1__*) ; 

NODE *
spec(FILE *fp)
{
	NODE *centry, *last, *pathparent, *cur;
	char *p, *e, *next;
	NODE ginfo, *root;
	char *buf, *tname, *ntname;
	size_t tnamelen, plen;

	root = NULL;
	centry = last = NULL;
	tname = NULL;
	tnamelen = 0;
	memset(&ginfo, 0, sizeof(ginfo));
	for (mtree_lineno = 0;
	    (buf = fparseln(fp, NULL, &mtree_lineno, NULL,
		FPARSELN_UNESCCOMM));
	    free(buf)) {
		/* Skip leading whitespace. */
		for (p = buf; *p && isspace((unsigned char)*p); ++p)
			continue;

		/* If nothing but whitespace, continue. */
		if (!*p)
			continue;

#ifdef DEBUG
		fprintf(stderr, "line %lu: {%s}\n",
		    (u_long)mtree_lineno, p);
#endif
		/* Grab file name, "$", "set", or "unset". */
		next = buf;
		while ((p = strsep(&next, " \t")) != NULL && *p == '\0')
			continue;
		if (p == NULL)
			mtree_err("missing field");

		if (p[0] == '/') {
			if (strcmp(p + 1, "set") == 0)
				set(next, &ginfo);
			else if (strcmp(p + 1, "unset") == 0)
				unset(next, &ginfo);
			else
				mtree_err("invalid specification `%s'", p);
			continue;
		}

		if (strcmp(p, "..") == 0) {
			/* Don't go up, if haven't gone down. */
			if (root == NULL)
				goto noparent;
			if (last->type != F_DIR || last->flags & F_DONE) {
				if (last == root)
					goto noparent;
				last = last->parent;
			}
			last->flags |= F_DONE;
			continue;

noparent:		mtree_err("no parent node");
		}

		plen = strlen(p) + 1;
		if (plen > tnamelen) {
			if ((ntname = realloc(tname, plen)) == NULL)
				mtree_err("realloc: %s", strerror(errno));
			tname = ntname;
			tnamelen = plen;
		}
		if (strunvis(tname, p) == -1)
			mtree_err("strunvis failed on `%s'", p);
		p = tname;

		pathparent = NULL;
		if (strchr(p, '/') != NULL) {
			cur = root;
			for (; (e = strchr(p, '/')) != NULL; p = e+1) {
				if (p == e)
					continue;	/* handle // */
				*e = '\0';
				if (strcmp(p, ".") != 0) {
					while (cur &&
					    strcmp(cur->name, p) != 0) {
						cur = cur->next;
					}
				}
				if (cur == NULL || cur->type != F_DIR) {
					mtree_err("%s: %s", tname,
					"missing directory in specification");
				}
				*e = '/';
				pathparent = cur;
				cur = cur->child;
			}
			if (*p == '\0')
				mtree_err("%s: empty leaf element", tname);
		}

		if ((centry = calloc(1, sizeof(NODE) + strlen(p))) == NULL)
			mtree_err("%s", strerror(errno));
		*centry = ginfo;
		centry->lineno = mtree_lineno;
		strcpy(centry->name, p);
#define	MAGIC	"?*["
		if (strpbrk(p, MAGIC))
			centry->flags |= F_MAGIC;
		set(next, centry);

		if (root == NULL) {
				/*
				 * empty tree
				 */
			/*
			 * Allow a bare "." root node by forcing it to
			 * type=dir for compatibility with FreeBSD.
			 */
			if (strcmp(centry->name, ".") == 0 && centry->type == 0)
				centry->type = F_DIR;
			if (strcmp(centry->name, ".") != 0 ||
			    centry->type != F_DIR)
				mtree_err(
				    "root node must be the directory `.'");
			last = root = centry;
			root->parent = root;
		} else if (pathparent != NULL) {
				/*
				 * full path entry; add or replace
				 */
			centry->parent = pathparent;
			addchild(pathparent, centry);
			last = centry;
		} else if (strcmp(centry->name, ".") == 0) {
				/*
				 * duplicate "." entry; always replace
				 */
			replacenode(root, centry);
		} else if (last->type == F_DIR && !(last->flags & F_DONE)) {
				/*
				 * new relative child in current dir;
				 * add or replace
				 */
			centry->parent = last;
			addchild(last, centry);
			last = centry;
		} else {
				/*
				 * new relative child in parent dir
				 * (after encountering ".." entry);
				 * add or replace
				 */
			centry->parent = last->parent;
			addchild(last->parent, centry);
			last = centry;
		}
	}
	return (root);
}