#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_8__ {int* val; } ;
struct statfs {char* f_mntfromname; char* f_mntonname; TYPE_2__ f_fsid; int /*<<< orphan*/  f_fstypename; } ;
struct nfscl_dumpmntopts {char* ndmnt_fname; char* ndmnt_buf; int ndmnt_blen; } ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  fsidbuf ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int /*<<< orphan*/  cl_auth; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKUNIQUE ; 
 scalar_t__ ENOENT ; 
 int MNT_BYFSID ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MOUNTPROC_UMNT ; 
 int /*<<< orphan*/  MOUNTPROG ; 
 int /*<<< orphan*/  MOUNTVERS3 ; 
 int /*<<< orphan*/  NFSSVC_DUMPMNTOPTS ; 
 int /*<<< orphan*/  REMOVE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  auth_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authsys_create_default () ; 
 int /*<<< orphan*/  clean_mtab (char*,char*,scalar_t__) ; 
 int clnt_call (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval) ; 
 TYPE_1__* clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  clnt_destroy (TYPE_1__*) ; 
 char* clnt_spcreateerror (char*) ; 
 char* clnt_sperror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int fflag ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_mtab () ; 
 int /*<<< orphan*/  getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/ * getmntentry (char*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namematch (struct addrinfo*) ; 
 scalar_t__ nfssvc (int /*<<< orphan*/ ,struct nfscl_dumpmntopts*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ read_mtab () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 scalar_t__ unmount (char*,int) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int /*<<< orphan*/  write_mtab (scalar_t__) ; 
 scalar_t__ xdr_dir ; 
 scalar_t__ xdr_void ; 

int
umountfs(struct statfs *sfs)
{
	char fsidbuf[64];
	enum clnt_stat clnt_stat;
	struct timeval try;
	struct addrinfo *ai, hints;
	int do_rpc;
	CLIENT *clp;
	char *nfsdirname, *orignfsdirname;
	char *hostp, *delimp;
	char buf[1024];
	struct nfscl_dumpmntopts dumpmntopts;
	const char *proto_ptr = NULL;

	ai = NULL;
	do_rpc = 0;
	hostp = NULL;
	nfsdirname = delimp = orignfsdirname = NULL;
	memset(&hints, 0, sizeof hints);

	if (strcmp(sfs->f_fstypename, "nfs") == 0) {
		if ((nfsdirname = strdup(sfs->f_mntfromname)) == NULL)
			err(1, "strdup");
		orignfsdirname = nfsdirname;
		if (*nfsdirname == '[' &&
		    (delimp = strchr(nfsdirname + 1, ']')) != NULL &&
		    *(delimp + 1) == ':') {
			hostp = nfsdirname + 1;
			nfsdirname = delimp + 2;
		} else if ((delimp = strrchr(nfsdirname, ':')) != NULL) {
			hostp = nfsdirname;
			nfsdirname = delimp + 1;
		}
		if (hostp != NULL) {
			*delimp = '\0';
			getaddrinfo(hostp, NULL, &hints, &ai);
			if (ai == NULL) {
				warnx("can't get net id for host");
			}
		}

		/*
		 * Check if we have to start the rpc-call later.
		 * If there are still identical nfs-names mounted,
		 * we skip the rpc-call. Obviously this has to
		 * happen before unmount(2), but it should happen
		 * after the previous namecheck.
		 * A non-NULL return means that this is the last
		 * mount from mntfromname that is still mounted.
		 */
		if (getmntentry(sfs->f_mntfromname, NULL, NULL,
		    CHECKUNIQUE) != NULL) {
			do_rpc = 1;
			proto_ptr = "udp";
			/*
			 * Try and find out whether this NFS mount is NFSv4 and
			 * what protocol is being used. If this fails, the
			 * default is NFSv2,3 and use UDP for the Unmount RPC.
			 */
			dumpmntopts.ndmnt_fname = sfs->f_mntonname;
			dumpmntopts.ndmnt_buf = buf;
			dumpmntopts.ndmnt_blen = sizeof(buf);
			if (nfssvc(NFSSVC_DUMPMNTOPTS, &dumpmntopts) >= 0) {
				if (strstr(buf, "nfsv4,") != NULL)
					do_rpc = 0;
				else if (strstr(buf, ",tcp,") != NULL)
					proto_ptr = "tcp";
			}
		}
	}

	if (!namematch(ai)) {
		free(orignfsdirname);
		return (1);
	}
	/* First try to unmount using the file system ID. */
	snprintf(fsidbuf, sizeof(fsidbuf), "FSID:%d:%d", sfs->f_fsid.val[0],
	    sfs->f_fsid.val[1]);
	if (unmount(fsidbuf, fflag | MNT_BYFSID) != 0) {
		/* XXX, non-root users get a zero fsid, so don't warn. */
		if (errno != ENOENT || sfs->f_fsid.val[0] != 0 ||
		    sfs->f_fsid.val[1] != 0)
			warn("unmount of %s failed", sfs->f_mntonname);
		if (errno != ENOENT) {
			free(orignfsdirname);
			return (1);
		}
		/* Compatibility for old kernels. */
		if (sfs->f_fsid.val[0] != 0 || sfs->f_fsid.val[1] != 0)
			warnx("retrying using path instead of file system ID");
		if (unmount(sfs->f_mntonname, fflag) != 0) {
			warn("unmount of %s failed", sfs->f_mntonname);
			free(orignfsdirname);
			return (1);
		}
	}
	/* Mark this this file system as unmounted. */
	getmntentry(NULL, NULL, &sfs->f_fsid, REMOVE);
	if (vflag)
		(void)printf("%s: unmount from %s\n", sfs->f_mntfromname,
		    sfs->f_mntonname);
	/*
	 * Report to mountd-server which nfsname
	 * has been unmounted.
	 */
	if (ai != NULL && !(fflag & MNT_FORCE) && do_rpc) {
		clp = clnt_create(hostp, MOUNTPROG, MOUNTVERS3, proto_ptr);
		if (clp  == NULL) {
			warnx("%s: %s", hostp,
			    clnt_spcreateerror("MOUNTPROG"));
			free(orignfsdirname);
			return (1);
		}
		clp->cl_auth = authsys_create_default();
		try.tv_sec = 20;
		try.tv_usec = 0;
		clnt_stat = clnt_call(clp, MOUNTPROC_UMNT, (xdrproc_t)xdr_dir,
		    nfsdirname, (xdrproc_t)xdr_void, (caddr_t)0, try);
		if (clnt_stat != RPC_SUCCESS) {
			warnx("%s: %s", hostp,
			    clnt_sperror(clp, "RPCMNT_UMOUNT"));
			free(orignfsdirname);
			return (1);
		}
		/*
		 * Remove the unmounted entry from /var/db/mounttab.
		 */
		if (read_mtab()) {
			clean_mtab(hostp, nfsdirname, vflag);
			if(!write_mtab(vflag))
				warnx("cannot remove mounttab entry %s:%s",
				    hostp, nfsdirname);
			free_mtab();
		}
		auth_destroy(clp->cl_auth);
		clnt_destroy(clp);
	}
	free(orignfsdirname);
	return (0);
}