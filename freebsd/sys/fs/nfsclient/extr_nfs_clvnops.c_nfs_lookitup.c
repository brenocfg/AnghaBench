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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {scalar_t__ na_type; } ;
struct nfsv4node {int dummy; } ;
struct nfsnode {struct nfsfh* n_fhp; struct nfsfh* n_v4; } ;
struct nfsfh {int n4_namelen; int nfh_len; int n4_fhlen; char* nfh_fh; int /*<<< orphan*/  n4_data; } ;
struct componentname {char* cn_nameptr; int cn_namelen; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  M_NFSFH ; 
 int /*<<< orphan*/  M_NFSV4NODE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFS4NODENAME (struct nfsfh*) ; 
 scalar_t__ NFSBCMP (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSBCOPY (char*,int /*<<< orphan*/ ,int) ; 
 struct vnode* NFSTOV (struct nfsnode*) ; 
 scalar_t__ NFS_CMPFH (struct nfsnode*,char*,int) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  fnv_32_buf (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nfsfh*,int /*<<< orphan*/ ) ; 
 struct nfsfh* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfscl_nget (int /*<<< orphan*/ ,struct vnode*,struct nfsfh*,struct componentname*,struct thread*,struct nfsnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfsrpc_lookup (struct vnode*,char*,int,struct ucred*,struct thread*,struct nfsvattr*,struct nfsvattr*,struct nfsfh**,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  vfs_hash_rehash (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
nfs_lookitup(struct vnode *dvp, char *name, int len, struct ucred *cred,
    struct thread *td, struct nfsnode **npp)
{
	struct vnode *newvp = NULL, *vp;
	struct nfsnode *np, *dnp = VTONFS(dvp);
	struct nfsfh *nfhp, *onfhp;
	struct nfsvattr nfsva, dnfsva;
	struct componentname cn;
	int error = 0, attrflag, dattrflag;
	u_int hash;

	error = nfsrpc_lookup(dvp, name, len, cred, td, &dnfsva, &nfsva,
	    &nfhp, &attrflag, &dattrflag, NULL);
	if (dattrflag)
		(void) nfscl_loadattrcache(&dvp, &dnfsva, NULL, NULL, 0, 1);
	if (npp && !error) {
		if (*npp != NULL) {
		    np = *npp;
		    vp = NFSTOV(np);
		    /*
		     * For NFSv4, check to see if it is the same name and
		     * replace the name, if it is different.
		     */
		    if (np->n_v4 != NULL && nfsva.na_type == VREG &&
			(np->n_v4->n4_namelen != len ||
			 NFSBCMP(name, NFS4NODENAME(np->n_v4), len) ||
			 dnp->n_fhp->nfh_len != np->n_v4->n4_fhlen ||
			 NFSBCMP(dnp->n_fhp->nfh_fh, np->n_v4->n4_data,
			 dnp->n_fhp->nfh_len))) {
#ifdef notdef
{ char nnn[100]; int nnnl;
nnnl = (len < 100) ? len : 99;
bcopy(name, nnn, nnnl);
nnn[nnnl] = '\0';
printf("replace=%s\n",nnn);
}
#endif
			    free(np->n_v4, M_NFSV4NODE);
			    np->n_v4 = malloc(
				sizeof (struct nfsv4node) +
				dnp->n_fhp->nfh_len + len - 1,
				M_NFSV4NODE, M_WAITOK);
			    np->n_v4->n4_fhlen = dnp->n_fhp->nfh_len;
			    np->n_v4->n4_namelen = len;
			    NFSBCOPY(dnp->n_fhp->nfh_fh, np->n_v4->n4_data,
				dnp->n_fhp->nfh_len);
			    NFSBCOPY(name, NFS4NODENAME(np->n_v4), len);
		    }
		    hash = fnv_32_buf(nfhp->nfh_fh, nfhp->nfh_len,
			FNV1_32_INIT);
		    onfhp = np->n_fhp;
		    /*
		     * Rehash node for new file handle.
		     */
		    vfs_hash_rehash(vp, hash);
		    np->n_fhp = nfhp;
		    if (onfhp != NULL)
			free(onfhp, M_NFSFH);
		    newvp = NFSTOV(np);
		} else if (NFS_CMPFH(dnp, nfhp->nfh_fh, nfhp->nfh_len)) {
		    free(nfhp, M_NFSFH);
		    VREF(dvp);
		    newvp = dvp;
		} else {
		    cn.cn_nameptr = name;
		    cn.cn_namelen = len;
		    error = nfscl_nget(dvp->v_mount, dvp, nfhp, &cn, td,
			&np, NULL, LK_EXCLUSIVE);
		    if (error)
			return (error);
		    newvp = NFSTOV(np);
		}
		if (!attrflag && *npp == NULL) {
			if (newvp == dvp)
				vrele(newvp);
			else
				vput(newvp);
			return (ENOENT);
		}
		if (attrflag)
			(void) nfscl_loadattrcache(&newvp, &nfsva, NULL, NULL,
			    0, 1);
	}
	if (npp && *npp == NULL) {
		if (error) {
			if (newvp) {
				if (newvp == dvp)
					vrele(newvp);
				else
					vput(newvp);
			}
		} else
			*npp = np;
	}
	if (error && NFS_ISV4(dvp))
		error = nfscl_maperr(td, error, (uid_t)0, (gid_t)0);
	return (error);
}