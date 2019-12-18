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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct devfs_dirent {int dummy; } ;

/* Variables and functions */
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_copy (struct mac_biba*,struct mac_biba*) ; 

__attribute__((used)) static void
biba_devfs_update(struct mount *mp, struct devfs_dirent *de,
    struct label *delabel, struct vnode *vp, struct label *vplabel)
{
	struct mac_biba *source, *dest;

	source = SLOT(vplabel);
	dest = SLOT(delabel);

	biba_copy(source, dest);
}