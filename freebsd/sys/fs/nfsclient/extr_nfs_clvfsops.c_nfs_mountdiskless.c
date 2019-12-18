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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct nfs_args {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFS_DEFAULT_NAMETIMEO ; 
 int /*<<< orphan*/  NFS_DEFAULT_NEGNAMETIMEO ; 
 int mountnfs (struct nfs_args*,struct mount*,struct sockaddr*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 struct sockaddr* sodupsockaddr (struct sockaddr*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
nfs_mountdiskless(char *path,
    struct sockaddr_in *sin, struct nfs_args *args, struct thread *td,
    struct vnode **vpp, struct mount *mp)
{
	struct sockaddr *nam;
	int dirlen, error;
	char *dirpath;

	/*
	 * Find the directory path in "path", which also has the server's
	 * name/ip address in it.
	 */
	dirpath = strchr(path, ':');
	if (dirpath != NULL)
		dirlen = strlen(++dirpath);
	else
		dirlen = 0;
	nam = sodupsockaddr((struct sockaddr *)sin, M_WAITOK);
	if ((error = mountnfs(args, mp, nam, path, NULL, 0, dirpath, dirlen,
	    NULL, 0, vpp, td->td_ucred, td, NFS_DEFAULT_NAMETIMEO, 
	    NFS_DEFAULT_NEGNAMETIMEO, 0)) != 0) {
		printf("nfs_mountroot: mount %s on /: %d\n", path, error);
		return (error);
	}
	return (0);
}