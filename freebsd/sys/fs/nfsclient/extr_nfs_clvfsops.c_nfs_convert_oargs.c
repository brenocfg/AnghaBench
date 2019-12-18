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
struct onfs_args {int /*<<< orphan*/  hostname; int /*<<< orphan*/  readahead; int /*<<< orphan*/  retrans; int /*<<< orphan*/  timeo; int /*<<< orphan*/  readdirsize; int /*<<< orphan*/  rsize; int /*<<< orphan*/  wsize; int /*<<< orphan*/  flags; int /*<<< orphan*/  fhsize; int /*<<< orphan*/  fh; int /*<<< orphan*/  proto; int /*<<< orphan*/  sotype; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct nfs_args {int /*<<< orphan*/  hostname; int /*<<< orphan*/  readahead; int /*<<< orphan*/  retrans; int /*<<< orphan*/  timeo; int /*<<< orphan*/  readdirsize; int /*<<< orphan*/  rsize; int /*<<< orphan*/  wsize; int /*<<< orphan*/  flags; int /*<<< orphan*/  fhsize; int /*<<< orphan*/  fh; int /*<<< orphan*/  proto; int /*<<< orphan*/  sotype; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_ARGSVERSION ; 

__attribute__((used)) static void
nfs_convert_oargs(struct nfs_args *args, struct onfs_args *oargs)
{

	args->version = NFS_ARGSVERSION;
	args->addr = oargs->addr;
	args->addrlen = oargs->addrlen;
	args->sotype = oargs->sotype;
	args->proto = oargs->proto;
	args->fh = oargs->fh;
	args->fhsize = oargs->fhsize;
	args->flags = oargs->flags;
	args->wsize = oargs->wsize;
	args->rsize = oargs->rsize;
	args->readdirsize = oargs->readdirsize;
	args->timeo = oargs->timeo;
	args->retrans = oargs->retrans;
	args->readahead = oargs->readahead;
	args->hostname = oargs->hostname;
}