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
struct smbnode {char* n_rpath; int n_rplen; } ;
struct smbfattr {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int SMBFS_DNP_SEP (struct smbnode*) ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  smbfs_attr_cacheenter (struct vnode*,struct smbfattr*) ; 
 int smbfs_node_alloc (struct mount*,struct vnode*,char*,int,char const*,int,int,struct smbfattr*,struct vnode**) ; 

int
smbfs_nget(struct mount *mp, struct vnode *dvp, const char *name, int nmlen,
	struct smbfattr *fap, struct vnode **vpp)
{
	struct smbnode *dnp, *np;
	struct vnode *vp;
	int error, sep;

	dnp = (dvp) ? VTOSMB(dvp) : NULL;
	sep = 0;
	if (dnp != NULL) {
		sep = SMBFS_DNP_SEP(dnp); 
		error = smbfs_node_alloc(mp, dvp, dnp->n_rpath, dnp->n_rplen, 
		    name, nmlen, sep, fap, &vp); 
	} else
		error = smbfs_node_alloc(mp, NULL, "\\", 1, name, nmlen, 
		    sep, fap, &vp); 
	if (error)
		return error;
	MPASS(vp != NULL);
	np = VTOSMB(vp);
	if (fap)
		smbfs_attr_cacheenter(vp, fap);
	*vpp = vp;
	return 0;
}