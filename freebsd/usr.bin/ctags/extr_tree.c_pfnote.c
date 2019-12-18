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
typedef  int /*<<< orphan*/  nbuf ;
struct TYPE_7__ {char* file; int lno; void* pat; scalar_t__ right; scalar_t__ left; void* entry; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 char EOS ; 
 int MAXTOKEN ; 
 int /*<<< orphan*/  add_node (TYPE_1__*,TYPE_1__*) ; 
 char* curfile ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free_tree (TYPE_1__*) ; 
 TYPE_1__* head ; 
 char const* lbuf ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  put_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xflag ; 

void
pfnote(const char *name, int ln)
{
	NODE	*np;
	char	*fp;
	char	nbuf[MAXTOKEN];

	/*NOSTRICT*/
	if (!(np = (NODE *)malloc(sizeof(NODE)))) {
		warnx("too many entries to sort");
		put_entries(head);
		free_tree(head);
		/*NOSTRICT*/
		if (!(head = np = (NODE *)malloc(sizeof(NODE))))
			errx(1, "out of space");
	}
	if (!xflag && !strcmp(name, "main")) {
		if (!(fp = strrchr(curfile, '/')))
			fp = curfile;
		else
			++fp;
		(void)snprintf(nbuf, sizeof(nbuf), "M%s", fp);
		fp = strrchr(nbuf, '.');
		if (fp && !fp[2])
			*fp = EOS;
		name = nbuf;
	}
	if (!(np->entry = strdup(name)))
		err(1, NULL);
	np->file = curfile;
	np->lno = ln;
	np->left = np->right = 0;
	if (!(np->pat = strdup(lbuf)))
		err(1, NULL);
	if (!head)
		head = np;
	else
		add_node(np, head);
}