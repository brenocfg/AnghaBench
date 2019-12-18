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
typedef  scalar_t__ uid_t ;
struct stat {int dummy; } ;
struct TYPE_3__ {int flags; scalar_t__ type; scalar_t__ st_uid; scalar_t__ st_flags; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_gid; struct TYPE_3__* child; int /*<<< orphan*/  slink; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 scalar_t__ F_DIR ; 
 int F_FLAGS ; 
 int F_GID ; 
 int F_GNAME ; 
 scalar_t__ F_LINK ; 
 int F_MODE ; 
 int F_OPT ; 
 int F_UID ; 
 int F_UNAME ; 
 int F_VISIT ; 
 int /*<<< orphan*/  S_IRWXU ; 
 scalar_t__ chflags (char*,scalar_t__) ; 
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 int chown (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dflag ; 
 int errno ; 
 int lchown (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 char* path ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ qflag ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 
 scalar_t__ symlink (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uflag ; 

__attribute__((used)) static void
miss(NODE *p, char *tail)
{
	int create;
	char *tp;
	const char *type, *what;
	int serr;

	for (; p; p = p->next) {
		if (p->flags & F_OPT && !(p->flags & F_VISIT))
			continue;
		if (p->type != F_DIR && (dflag || p->flags & F_VISIT))
			continue;
		(void)strcpy(tail, p->name);
		if (!(p->flags & F_VISIT)) {
			/* Don't print missing message if file exists as a
			   symbolic link and the -q flag is set. */
			struct stat statbuf;

			if (qflag && stat(path, &statbuf) == 0)
				p->flags |= F_VISIT;
			else
				(void)printf("%s missing", path);
		}
		if (p->type != F_DIR && p->type != F_LINK) {
			putchar('\n');
			continue;
		}

		create = 0;
		if (p->type == F_LINK)
			type = "symlink";
		else
			type = "directory";
		if (!(p->flags & F_VISIT) && uflag) {
			if (!(p->flags & (F_UID | F_UNAME)))
				(void)printf(" (%s not created: user not specified)", type);
			else if (!(p->flags & (F_GID | F_GNAME)))
				(void)printf(" (%s not created: group not specified)", type);
			else if (p->type == F_LINK) {
				if (symlink(p->slink, path))
					(void)printf(" (symlink not created: %s)\n",
					    strerror(errno));
				else
					(void)printf(" (created)\n");
				if (lchown(path, p->st_uid, p->st_gid) == -1) {
					serr = errno;
					if (p->st_uid == (uid_t)-1)
						what = "group";
					else if (lchown(path, (uid_t)-1,
					    p->st_gid) == -1)
						what = "user & group";
					else {
						what = "user";
						errno = serr;
					}
					(void)printf("%s: %s not modified: %s"
					    "\n", path, what, strerror(errno));
				}
				continue;
			} else if (!(p->flags & F_MODE))
			    (void)printf(" (directory not created: mode not specified)");
			else if (mkdir(path, S_IRWXU))
				(void)printf(" (directory not created: %s)",
				    strerror(errno));
			else {
				create = 1;
				(void)printf(" (created)");
			}
		}
		if (!(p->flags & F_VISIT))
			(void)putchar('\n');

		for (tp = tail; *tp; ++tp);
		*tp = '/';
		miss(p->child, tp + 1);
		*tp = '\0';

		if (!create && !uflag)
			continue;
		if (chown(path, p->st_uid, p->st_gid) == -1) {
			serr = errno;
			if (p->st_uid == (uid_t)-1)
				what = "group";
			else if (chown(path, (uid_t)-1, p->st_gid) == -1)
				what = "user & group";
			else {
				what = "user";
				errno = serr;
			}
			(void)printf("%s: %s not modified: %s\n",
			    path, what, strerror(errno));
		}
		if (chmod(path, p->st_mode))
			(void)printf("%s: permissions not set: %s\n",
			    path, strerror(errno));
		if ((p->flags & F_FLAGS) && p->st_flags &&
		    chflags(path, p->st_flags))
			(void)printf("%s: file flags not set: %s\n",
			    path, strerror(errno));
	}
}