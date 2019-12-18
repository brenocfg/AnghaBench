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
typedef  int /*<<< orphan*/  u_char ;
struct thread {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct nfs_args {int flags; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int AUTH_UNIX ; 
 int EBADRPC ; 
 int NFSMNT_NFSV3 ; 
 int NFSX_V2FH ; 
 int NFSX_V3FHMAX ; 
 int /*<<< orphan*/  NFS_PROG ; 
 int /*<<< orphan*/  NFS_VER2 ; 
 int /*<<< orphan*/  NFS_VER3 ; 
 int /*<<< orphan*/  RPCMNT_MOUNT ; 
 int /*<<< orphan*/  RPCMNT_VER1 ; 
 int /*<<< orphan*/  RPCMNT_VER3 ; 
 int /*<<< orphan*/  RPCPROG_MNT ; 
 int krpc_call (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf**,int /*<<< orphan*/ *,struct thread*) ; 
 int krpc_portmap (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ xdr_int_decode (struct mbuf**,int*) ; 
 scalar_t__ xdr_opaque_decode (struct mbuf**,int /*<<< orphan*/ *,int) ; 
 struct mbuf* xdr_string_encode (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
md_mount(struct sockaddr_in *mdsin, char *path, u_char *fhp, int *fhsizep,
    struct nfs_args *args, struct thread *td)
{
	struct mbuf *m;
	int error;
	int authunixok;
	int authcount;
	int authver;

#define	RPCPROG_MNT	100005
#define	RPCMNT_VER1	1
#define RPCMNT_VER3	3
#define	RPCMNT_MOUNT	1
#define	AUTH_SYS	1		/* unix style (uid, gids) */
#define AUTH_UNIX	AUTH_SYS

	/* XXX honor v2/v3 flags in args->flags? */
#ifdef BOOTP_NFSV3
	/* First try NFS v3 */
	/* Get port number for MOUNTD. */
	error = krpc_portmap(mdsin, RPCPROG_MNT, RPCMNT_VER3,
			     &mdsin->sin_port, td);
	if (error == 0) {
		m = xdr_string_encode(path, strlen(path));

		/* Do RPC to mountd. */
		error = krpc_call(mdsin, RPCPROG_MNT, RPCMNT_VER3,
				  RPCMNT_MOUNT, &m, NULL, td);
	}
	if (error == 0) {
		args->flags |= NFSMNT_NFSV3;
	} else {
#endif
		/* Fallback to NFS v2 */

		/* Get port number for MOUNTD. */
		error = krpc_portmap(mdsin, RPCPROG_MNT, RPCMNT_VER1,
				     &mdsin->sin_port, td);
		if (error != 0)
			return error;

		m = xdr_string_encode(path, strlen(path));

		/* Do RPC to mountd. */
		error = krpc_call(mdsin, RPCPROG_MNT, RPCMNT_VER1,
				  RPCMNT_MOUNT, &m, NULL, td);
		if (error != 0)
			return error;	/* message already freed */

#ifdef BOOTP_NFSV3
	}
#endif

	if (xdr_int_decode(&m, &error) != 0 || error != 0)
		goto bad;

	if ((args->flags & NFSMNT_NFSV3) != 0) {
		if (xdr_int_decode(&m, fhsizep) != 0 ||
		    *fhsizep > NFSX_V3FHMAX ||
		    *fhsizep <= 0)
			goto bad;
	} else
		*fhsizep = NFSX_V2FH;

	if (xdr_opaque_decode(&m, fhp, *fhsizep) != 0)
		goto bad;

	if (args->flags & NFSMNT_NFSV3) {
		if (xdr_int_decode(&m, &authcount) != 0)
			goto bad;
		authunixok = 0;
		if (authcount < 0 || authcount > 100)
			goto bad;
		while (authcount > 0) {
			if (xdr_int_decode(&m, &authver) != 0)
				goto bad;
			if (authver == AUTH_UNIX)
				authunixok = 1;
			authcount--;
		}
		if (authunixok == 0)
			goto bad;
	}

	/* Set port number for NFS use. */
	error = krpc_portmap(mdsin, NFS_PROG,
			     (args->flags &
			      NFSMNT_NFSV3) ? NFS_VER3 : NFS_VER2,
			     &mdsin->sin_port, td);

	goto out;

bad:
	error = EBADRPC;

out:
	m_freem(m);
	return error;
}