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
struct vnode {scalar_t__ v_data; } ;
struct smbnode {scalar_t__ n_parent; scalar_t__ n_nmlen; int /*<<< orphan*/  n_name; } ;
struct smbcmp {scalar_t__ n_parent; scalar_t__ n_nmlen; int /*<<< orphan*/  n_name; } ;

/* Variables and functions */
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __inline
smbfs_vnode_cmp(struct vnode *vp, void *_sc) 
{
	struct smbnode *np;
	struct smbcmp *sc;

	np = (struct smbnode *) vp->v_data;
	sc = (struct smbcmp *) _sc;
	if (np->n_parent != sc->n_parent || np->n_nmlen != sc->n_nmlen ||
	    bcmp(sc->n_name, np->n_name, sc->n_nmlen) != 0)
		return 1;
	return 0;
}