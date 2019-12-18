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
struct pfstab {struct fstab* pf_fstab; } ;
struct fstab {int /*<<< orphan*/  fs_vfstype; int /*<<< orphan*/  fs_type; } ;

/* Variables and functions */
 char* FSTAB_RO ; 
 char* FSTAB_RQ ; 
 char* FSTAB_RW ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pfstab*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PATH_FSTAB ; 
 struct fstab* allocfsent (struct fstab*) ; 
 int /*<<< orphan*/  endfsent () ; 
 int /*<<< orphan*/  errno ; 
 struct fstab* getfsent () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_list ; 
 int /*<<< orphan*/  quit (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ setfsent () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table ; 

void
dump_getfstab(void)
{
	struct fstab *fs;
	struct pfstab *pf;

	if (setfsent() == 0) {
		msg("Can't open %s for dump table information: %s\n",
		    _PATH_FSTAB, strerror(errno));
		return;
	}
	while ((fs = getfsent()) != NULL) {
		if ((strcmp(fs->fs_type, FSTAB_RW) &&
		    strcmp(fs->fs_type, FSTAB_RO) &&
		    strcmp(fs->fs_type, FSTAB_RQ)) ||
		    strcmp(fs->fs_vfstype, "ufs"))
			continue;
		fs = allocfsent(fs);
		if ((pf = (struct pfstab *)malloc(sizeof (*pf))) == NULL)
			quit("%s\n", strerror(errno));
		pf->pf_fstab = fs;
		SLIST_INSERT_HEAD(&table, pf, pf_list);
	}
	(void) endfsent();
}