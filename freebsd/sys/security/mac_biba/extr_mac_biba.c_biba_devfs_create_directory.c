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
struct mount {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct devfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_BIBA_TYPE_HIGH ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_set_effective (struct mac_biba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
biba_devfs_create_directory(struct mount *mp, char *dirname, int dirnamelen,
    struct devfs_dirent *de, struct label *delabel)
{
	struct mac_biba *mb;

	mb = SLOT(delabel);

	biba_set_effective(mb, MAC_BIBA_TYPE_HIGH, 0, NULL);
}