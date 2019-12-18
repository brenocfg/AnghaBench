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
struct nfsmount {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 struct nfsmount* VFSTONFS (struct mount*) ; 
 int /*<<< orphan*/  newnfs_nmcancelreqs (struct nfsmount*) ; 

__attribute__((used)) static void
nfs_purge(struct mount *mp)
{
	struct nfsmount *nmp = VFSTONFS(mp);

	newnfs_nmcancelreqs(nmp);
}