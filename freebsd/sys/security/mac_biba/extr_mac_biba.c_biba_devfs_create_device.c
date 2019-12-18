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
struct ucred {int dummy; } ;
struct mount {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct devfs_dirent {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int MAC_BIBA_TYPE_EQUAL ; 
 int MAC_BIBA_TYPE_HIGH ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_set_effective (struct mac_biba*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* devtoname (struct cdev*) ; 
 scalar_t__ ptys_equal ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
biba_devfs_create_device(struct ucred *cred, struct mount *mp,
    struct cdev *dev, struct devfs_dirent *de, struct label *delabel)
{
	struct mac_biba *mb;
	const char *dn;
	int biba_type;

	mb = SLOT(delabel);
	dn = devtoname(dev);
	if (strcmp(dn, "null") == 0 ||
	    strcmp(dn, "zero") == 0 ||
	    strcmp(dn, "random") == 0 ||
	    strncmp(dn, "fd/", strlen("fd/")) == 0)
		biba_type = MAC_BIBA_TYPE_EQUAL;
	else if (ptys_equal &&
	    (strncmp(dn, "ttyp", strlen("ttyp")) == 0 ||
	    strncmp(dn, "pts/", strlen("pts/")) == 0 ||
	    strncmp(dn, "ptyp", strlen("ptyp")) == 0))
		biba_type = MAC_BIBA_TYPE_EQUAL;
	else
		biba_type = MAC_BIBA_TYPE_HIGH;
	biba_set_effective(mb, biba_type, 0, NULL);
}