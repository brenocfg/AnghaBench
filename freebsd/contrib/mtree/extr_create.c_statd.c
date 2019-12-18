#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
typedef  scalar_t__ u_short ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  m ;
typedef  int gid_t ;
typedef  int /*<<< orphan*/  g ;
typedef  int /*<<< orphan*/  f ;
struct TYPE_7__ {TYPE_1__* fts_statp; struct TYPE_7__* fts_link; } ;
struct TYPE_6__ {int st_mode; int st_gid; int st_uid; int st_flags; } ;
typedef  TYPE_2__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FLAGS2INDEX (int) ; 
 int F_FLAGS ; 
 int F_GID ; 
 int F_GNAME ; 
 int F_MODE ; 
 scalar_t__ F_NETBSD6 ; 
 int F_NLINK ; 
 int F_UID ; 
 int F_UNAME ; 
 int MBITS ; 
 int MTREE_MAXFLAGS ; 
 int MTREE_MAXGID ; 
 int MTREE_MAXMODE ; 
 int MTREE_MAXUID ; 
 int /*<<< orphan*/  RP (TYPE_2__*) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ dflag ; 
 scalar_t__ errno ; 
 char* flags_to_string (int,char*) ; 
 scalar_t__ flavor ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* fts_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* group_from_gid (int,int) ; 
 int keys ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtree_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 char* user_from_uid (int,int) ; 

__attribute__((used)) static int
statd(FILE *fp, FTS *t, FTSENT *parent, uid_t *puid, gid_t *pgid, mode_t *pmode,
    u_long *pflags)
{
	FTSENT *p;
	gid_t sgid;
	uid_t suid;
	mode_t smode;
	u_long sflags = 0;
	const char *name = NULL;
	gid_t savegid;
	uid_t saveuid;
	mode_t savemode;
	u_long saveflags;
	u_short maxgid, maxuid, maxmode, maxflags;
	u_short g[MTREE_MAXGID], u[MTREE_MAXUID],
		m[MTREE_MAXMODE], f[MTREE_MAXFLAGS];
	static int first = 1;

	savegid = *pgid;
	saveuid = *puid;
	savemode = *pmode;
	saveflags = *pflags;
	if ((p = fts_children(t, 0)) == NULL) {
		if (errno)
			mtree_err("%s: %s", RP(parent), strerror(errno));
		return (1);
	}

	memset(g, 0, sizeof(g));
	memset(u, 0, sizeof(u));
	memset(m, 0, sizeof(m));
	memset(f, 0, sizeof(f));

	maxuid = maxgid = maxmode = maxflags = 0;
	for (; p; p = p->fts_link) {
		if (flavor == F_NETBSD6 || !dflag ||
		    (dflag && S_ISDIR(p->fts_statp->st_mode))) {
			smode = p->fts_statp->st_mode & MBITS;
			if (smode < MTREE_MAXMODE && ++m[smode] > maxmode) {
				savemode = smode;
				maxmode = m[smode];
			}
			sgid = p->fts_statp->st_gid;
			if (sgid < MTREE_MAXGID && ++g[sgid] > maxgid) {
				savegid = sgid;
				maxgid = g[sgid];
			}
			suid = p->fts_statp->st_uid;
			if (suid < MTREE_MAXUID && ++u[suid] > maxuid) {
				saveuid = suid;
				maxuid = u[suid];
			}

#if HAVE_STRUCT_STAT_ST_FLAGS
			sflags = FLAGS2INDEX(p->fts_statp->st_flags);
			if (sflags < MTREE_MAXFLAGS && ++f[sflags] > maxflags) {
				saveflags = p->fts_statp->st_flags;
				maxflags = f[sflags];
			}
#endif
		}
	}
	/*
	 * If the /set record is the same as the last one we do not need to
	 * output a new one.  So first we check to see if anything changed.
	 * Note that we always output a /set record for the first directory.
	 */
	if (((keys & (F_UNAME | F_UID)) && (*puid != saveuid)) ||
	    ((keys & (F_GNAME | F_GID)) && (*pgid != savegid)) ||
	    ((keys & F_MODE) && (*pmode != savemode)) || 
	    ((keys & F_FLAGS) && (*pflags != saveflags)) ||
	    first) {
		first = 0;
		if (flavor != F_NETBSD6 && dflag)
			fprintf(fp, "/set type=dir");
		else
			fprintf(fp, "/set type=file");
		if (keys & (F_UID | F_UNAME)) {
			if (keys & F_UNAME &&
			    (name = user_from_uid(saveuid, 1)) != NULL)
				fprintf(fp, " uname=%s", name);
			if (keys & F_UID || (keys & F_UNAME && name == NULL))
				fprintf(fp, " uid=%lu", (u_long)saveuid);
		}
		if (keys & (F_GID | F_GNAME)) {
			if (keys & F_GNAME &&
			    (name = group_from_gid(savegid, 1)) != NULL)
				fprintf(fp, " gname=%s", name);
			if (keys & F_GID || (keys & F_GNAME && name == NULL))
				fprintf(fp, " gid=%lu", (u_long)savegid);
		}
		if (keys & F_MODE)
			fprintf(fp, " mode=%#lo", (u_long)savemode);
		if (keys & F_NLINK)
			fprintf(fp, " nlink=1");
		if (keys & F_FLAGS) {
			char *str = flags_to_string(saveflags, "none");
			fprintf(fp, " flags=%s", str);
			free(str);
		}
		fprintf(fp, "\n");
		*puid = saveuid;
		*pgid = savegid;
		*pmode = savemode;
		*pflags = saveflags;
	}
	return (0);
}