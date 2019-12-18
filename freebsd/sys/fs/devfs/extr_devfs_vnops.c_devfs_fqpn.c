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
struct devfs_mount {struct devfs_dirent* dm_rootdir; int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {TYPE_1__* de_dirent; } ;
struct componentname {int cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
struct TYPE_2__ {int d_namlen; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_LOCKED ; 
 int SPECNAMELEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 struct devfs_dirent* devfs_parent_dirent (struct devfs_dirent*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *
devfs_fqpn(char *buf, struct devfs_mount *dmp, struct devfs_dirent *dd,
    struct componentname *cnp)
{
	int i;
	struct devfs_dirent *de;

	sx_assert(&dmp->dm_lock, SA_LOCKED);

	i = SPECNAMELEN;
	buf[i] = '\0';
	if (cnp != NULL)
		i -= cnp->cn_namelen;
	if (i < 0)
		 return (NULL);
	if (cnp != NULL)
		bcopy(cnp->cn_nameptr, buf + i, cnp->cn_namelen);
	de = dd;
	while (de != dmp->dm_rootdir) {
		if (cnp != NULL || i < SPECNAMELEN) {
			i--;
			if (i < 0)
				 return (NULL);
			buf[i] = '/';
		}
		i -= de->de_dirent->d_namlen;
		if (i < 0)
			 return (NULL);
		bcopy(de->de_dirent->d_name, buf + i,
		    de->de_dirent->d_namlen);
		de = devfs_parent_dirent(de);
		if (de == NULL)
			return (NULL);
	}
	return (buf + i);
}