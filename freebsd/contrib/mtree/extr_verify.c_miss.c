#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_3__ {int flags; int type; int st_mode; int st_flags; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; struct TYPE_3__* child; int /*<<< orphan*/  slink; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
#define  F_BLOCK 131 
#define  F_CHAR 130 
 int F_DEV ; 
#define  F_DIR 129 
 int F_FLAGS ; 
 int F_GID ; 
 int F_GNAME ; 
#define  F_LINK 128 
 int F_MODE ; 
 int F_OPT ; 
 int F_SLINK ; 
 int F_UID ; 
 int F_UNAME ; 
 int F_VISIT ; 
 int SP_FLGS ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ iflag ; 
 scalar_t__ lchflags (char*,int) ; 
 scalar_t__ lchmod (char*,int) ; 
 scalar_t__ lchown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int mknod (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mtree_Wflag ; 
 int /*<<< orphan*/  mtree_err (char*,int /*<<< orphan*/ ) ; 
 int nodetoino (int) ; 
 int /*<<< orphan*/  nodetype (int) ; 
 char* path ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ qflag ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symlink (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uflag ; 

__attribute__((used)) static void
miss(NODE *p, char *tail)
{
	int create;
	char *tp;
	const char *type;
	u_int32_t flags;

	for (; p; p = p->next) {
		if (p->flags & F_OPT && !(p->flags & F_VISIT))
			continue;
		if (p->type != F_DIR && (dflag || p->flags & F_VISIT))
			continue;
		strcpy(tail, p->name);
		if (!(p->flags & F_VISIT)) {
			/* Don't print missing message if file exists as a 
			   symbolic link and the -q flag is set. */
			struct stat statbuf;

			if (qflag && stat(path, &statbuf) == 0 &&
			    S_ISDIR(statbuf.st_mode))
				p->flags |= F_VISIT;
			else
				(void)printf("%s missing", path);
		}
		switch (p->type) {
		case F_BLOCK:
		case F_CHAR:
			type = "device";
			break;
		case F_DIR:
			type = "directory";
			break;
		case F_LINK:
			type = "symlink";
			break;
		default:
			putchar('\n');
			continue;
		}

		create = 0;
		if (!(p->flags & F_VISIT) && uflag) {
			if (mtree_Wflag || p->type == F_LINK)
				goto createit;
			if (!(p->flags & (F_UID | F_UNAME)))
			    printf(
				" (%s not created: user not specified)", type);
			else if (!(p->flags & (F_GID | F_GNAME)))
			    printf(
				" (%s not created: group not specified)", type);
			else if (!(p->flags & F_MODE))
			    printf(
				" (%s not created: mode not specified)", type);
			else
 createit:
			switch (p->type) {
			case F_BLOCK:
			case F_CHAR:
				if (mtree_Wflag)
					continue;
				if (!(p->flags & F_DEV))
					printf(
				    " (%s not created: device not specified)",
					    type);
				else if (mknod(path,
				    p->st_mode | nodetoino(p->type),
				    p->st_rdev) == -1)
					printf(" (%s not created: %s)\n",
					    type, strerror(errno));
				else
					create = 1;
				break;
			case F_LINK:
				if (!(p->flags & F_SLINK))
					printf(
				    " (%s not created: link not specified)\n",
					    type);
				else if (symlink(p->slink, path))
					printf(
					    " (%s not created: %s)\n",
					    type, strerror(errno));
				else
					create = 1;
				break;
			case F_DIR:
				if (mkdir(path, S_IRWXU|S_IRWXG|S_IRWXO))
					printf(" (not created: %s)",
					    strerror(errno));
				else
					create = 1;
				break;
			default:
				mtree_err("can't create create %s",
				    nodetype(p->type));
			}
		}
		if (create)
			printf(" (created)");
		if (p->type == F_DIR) {
			if (!(p->flags & F_VISIT))
				putchar('\n');
			for (tp = tail; *tp; ++tp)
				continue;
			*tp = '/';
			miss(p->child, tp + 1);
			*tp = '\0';
		} else
			putchar('\n');

		if (!create || mtree_Wflag)
			continue;
		if ((p->flags & (F_UID | F_UNAME)) &&
		    (p->flags & (F_GID | F_GNAME)) &&
		    (lchown(path, p->st_uid, p->st_gid))) {
			printf("%s: user/group/mode not modified: %s\n",
			    path, strerror(errno));
			printf("%s: warning: file mode %snot set\n", path,
			    (p->flags & F_FLAGS) ? "and file flags " : "");
			continue;
		}
		if (p->flags & F_MODE) {
			if (lchmod(path, p->st_mode))
				printf("%s: permissions not set: %s\n",
				    path, strerror(errno));
		}
#if HAVE_STRUCT_STAT_ST_FLAGS
		if ((p->flags & F_FLAGS) && p->st_flags) {
			if (iflag)
				flags = p->st_flags;
			else
				flags = p->st_flags & ~SP_FLGS;
			if (lchflags(path, flags))
				printf("%s: file flags not set: %s\n",
				    path, strerror(errno));
		}
#endif	/* HAVE_STRUCT_STAT_ST_FLAGS */
	}
}