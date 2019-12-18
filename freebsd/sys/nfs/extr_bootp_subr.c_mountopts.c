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
struct nfs_args {int flags; int /*<<< orphan*/  sotype; void* wsize; void* rsize; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 void* BOOTP_BLOCKSIZE ; 
 int NFSMNT_RESVPORT ; 
 int NFSMNT_RSIZE ; 
 int NFSMNT_WSIZE ; 
 int /*<<< orphan*/  NFS_ARGSVERSION ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  nfs_parse_options (char*,struct nfs_args*) ; 

__attribute__((used)) static void
mountopts(struct nfs_args *args, char *p)
{
	args->version = NFS_ARGSVERSION;
	args->rsize = BOOTP_BLOCKSIZE;
	args->wsize = BOOTP_BLOCKSIZE;
	args->flags = NFSMNT_RSIZE | NFSMNT_WSIZE | NFSMNT_RESVPORT;
	args->sotype = SOCK_DGRAM;
	if (p != NULL)
		nfs_parse_options(p, args);
}