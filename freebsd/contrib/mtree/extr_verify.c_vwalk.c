#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int fts_info; int fts_level; int /*<<< orphan*/  fts_accpath; TYPE_1__* fts_statp; int /*<<< orphan*/  fts_name; int /*<<< orphan*/  fts_errno; int /*<<< orphan*/  fts_path; } ;
struct TYPE_11__ {int flags; scalar_t__ type; struct TYPE_11__* child; int /*<<< orphan*/  name; struct TYPE_11__* next; struct TYPE_11__* prev; struct TYPE_11__* parent; } ;
struct TYPE_10__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ NODE ;
typedef  TYPE_3__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int /*<<< orphan*/  FNM_PATHNAME ; 
#define  FTS_D 133 
#define  FTS_DNR 132 
#define  FTS_DP 131 
#define  FTS_ERR 130 
#define  FTS_NS 129 
 int /*<<< orphan*/  FTS_SKIP ; 
#define  FTS_SL 128 
 scalar_t__ F_DIR ; 
 int F_IGN ; 
 int F_MAGIC ; 
 int F_NOCHANGE ; 
 int F_VISIT ; 
 int MISMATCHEXIT ; 
 char* RP (TYPE_3__*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ check_excludes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ compare (TYPE_2__*,TYPE_3__*) ; 
 char* crc_total ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  eflag ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  find_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftsoptions ; 
 char* fullpath ; 
 int /*<<< orphan*/  mtree_err (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ rflag ; 
 scalar_t__ rmdir (int /*<<< orphan*/ ) ; 
 TYPE_2__* root ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,char*) ; 

__attribute__((used)) static int
vwalk(void)
{
	FTS *t;
	FTSENT *p;
	NODE *ep, *level;
	int specdepth, rval;
	char *argv[2];
	char  dot[] = ".";
	argv[0] = dot;
	argv[1] = NULL;

	if ((t = fts_open(argv, ftsoptions, NULL)) == NULL)
		mtree_err("fts_open: %s", strerror(errno));
	level = root;
	specdepth = rval = 0;
	while ((p = fts_read(t)) != NULL) {
		if (check_excludes(p->fts_name, p->fts_path)) {
			fts_set(t, p, FTS_SKIP);
			continue;
		}
		if (!find_only(p->fts_path)) {
			fts_set(t, p, FTS_SKIP);
			continue;
		}
		switch(p->fts_info) {
		case FTS_D:
		case FTS_SL:
			break;
		case FTS_DP:
			if (specdepth > p->fts_level) {
				for (level = level->parent; level->prev;
				    level = level->prev)
					continue;
				--specdepth;
			}
			continue;
		case FTS_DNR:
		case FTS_ERR:
		case FTS_NS:
			warnx("%s: %s", RP(p), strerror(p->fts_errno));
			continue;
		default:
			if (dflag)
				continue;
		}

		if (specdepth != p->fts_level)
			goto extra;
		for (ep = level; ep; ep = ep->next)
			if ((ep->flags & F_MAGIC &&
			    !fnmatch(ep->name, p->fts_name, FNM_PATHNAME)) ||
			    !strcmp(ep->name, p->fts_name)) {
				ep->flags |= F_VISIT;
				if ((ep->flags & F_NOCHANGE) == 0 &&
				    compare(ep, p))
					rval = MISMATCHEXIT;
				if (!(ep->flags & F_IGN) &&
				    ep->type == F_DIR &&
				    p->fts_info == FTS_D) {
					if (ep->child) {
						level = ep->child;
						++specdepth;
					}
				} else
					fts_set(t, p, FTS_SKIP);
				break;
			}

		if (ep)
			continue;
 extra:
		if (!eflag && !(dflag && p->fts_info == FTS_SL)) {
			printf("extra: %s", RP(p));
			if (rflag) {
				if ((S_ISDIR(p->fts_statp->st_mode)
				    ? rmdir : unlink)(p->fts_accpath)) {
					printf(", not removed: %s",
					    strerror(errno));
				} else
					printf(", removed");
			}
			putchar('\n');
		}
		fts_set(t, p, FTS_SKIP);
	}
	fts_close(t);
	if (sflag)
		warnx("%s checksum: %u", fullpath, crc_total);
	return (rval);
}