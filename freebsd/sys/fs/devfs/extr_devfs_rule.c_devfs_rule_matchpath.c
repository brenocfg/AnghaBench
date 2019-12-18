#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devfs_rule {int /*<<< orphan*/  dr_pathptrn; } ;
struct devfs_mount {struct devfs_dirent* dm_rootdir; } ;
struct devfs_krule {struct devfs_rule dk_rule; } ;
struct devfs_dirent {int de_flags; TYPE_1__* de_dirent; } ;
struct cdev {char* si_name; } ;
struct TYPE_2__ {scalar_t__ d_type; } ;

/* Variables and functions */
 int DE_DOT ; 
 int DE_DOTDOT ; 
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_LNK ; 
 int /*<<< orphan*/  FNM_PATHNAME ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ SPECNAMELEN ; 
 char* devfs_fqpn (char*,struct devfs_mount*,struct devfs_dirent*,int /*<<< orphan*/ *) ; 
 struct cdev* devfs_rule_getdev (struct devfs_dirent*) ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devfs_rule_matchpath(struct devfs_krule *dk, struct devfs_mount *dm,
    struct devfs_dirent *de)
{
	struct devfs_rule *dr = &dk->dk_rule;
	struct cdev *dev;
	int match;
	char *pname, *specname;

	specname = NULL;
	dev = devfs_rule_getdev(de);
	if (dev != NULL)
		pname = dev->si_name;
	else if (de->de_dirent->d_type == DT_LNK ||
	    (de->de_dirent->d_type == DT_DIR && de != dm->dm_rootdir &&
	    (de->de_flags & (DE_DOT | DE_DOTDOT)) == 0)) {
		specname = malloc(SPECNAMELEN + 1, M_TEMP, M_WAITOK);
		pname = devfs_fqpn(specname, dm, de, NULL);
	} else
		return (0);

	KASSERT(pname != NULL, ("devfs_rule_matchpath: NULL pname"));
	match = fnmatch(dr->dr_pathptrn, pname, FNM_PATHNAME) == 0;
	free(specname, M_TEMP);
	return (match);
}